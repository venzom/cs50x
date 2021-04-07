import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import json
import string
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    stocks = db.execute("""SELECT symbol, shares FROM transactions
                        WHERE user = :user""", user=session["user_id"])
    stock_total = 0
    total = 0.0
    for stock in stocks:
        quote = lookup(stock["symbol"])
        price = float(quote['price'])
        symbol = stock["symbol"]
        shares = float(stock["shares"])
        stock_total = price * shares
        db.execute("""UPDATE transactions SET price = :price,
                  total = :total WHERE user = :user
                  AND symbol = :symbol""", user=session["user_id"], price=price, \
                  total=stock_total, symbol=symbol)
        total += stock_total

    stocks = db.execute("SELECT * FROM transactions WHERE user = :user", user=session["user_id"])
    rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    cash = float(rows[0]["cash"])
    total += cash
    return render_template("index.html", stocks=stocks, total=total, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    if request.method == "POST":
        symbol = str.upper(request.form.get("symbol"))
        if not symbol:
            return apology("Missing symbol")
        shares = int(request.form.get("shares"))
        if not shares:
            return apology("missing shares")
        if shares < 1:
            return apology("invalid shares")
        else:
            quote = lookup(symbol)
            if not quote:
                return apology("invalid symbol")
            rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
            cash = float(rows[0]["cash"])
            total = float(quote['price'] * shares)
            price = float(quote['price'])
            name = str(quote['name'])
            if cash <= total:
                return apology("can't afford")
            check = db.execute("""SELECT * FROM transactions
                               WHERE user = :user AND symbol = :symbol""", \
                               user = session["user_id"], symbol = symbol)

            if len(check) == 0:
                db.execute("""INSERT INTO transactions (user, symbol, name, shares, price, total)
                           VALUES (:user, :symbol, :name, :shares, :price, :price * :shares)""",  \
                           user = session["user_id"], symbol=symbol, name=name,\
                           shares=shares, price=price)
            else:
                db.execute("""UPDATE transactions SET
                           shares = shares + :bought
                           WHERE user = :user""", user = session["user_id"], bought=shares)
                # db.execute("""UPDATE transactions SET total = shares * price
                #           WHERE user = :user""", user=session["user_id"])
            db.execute("""INSERT INTO history (user, symbol, shares, price) VALUES (:user, :symbol, :shares, :price)""", \
                      user=session["user_id"], symbol=symbol, shares=shares, price=price)
            db.execute("""UPDATE users SET cash = cash - :total WHERE id = :id""", \
                       id = session["user_id"], total = total)
            return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM history WHERE user = :user", user=session["user_id"])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing Symbol")
        else:
            quote = lookup(symbol)
            if not quote:
                return apology("invalid symbol")
            return render_template("quotes.html", displayquote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        chars = set("0123456789")
        username = request.form.get("username")
        if not username:
            return render_template("register.html", message="Please provide a username")
        password = request.form.get("password")
        if not password:
            return render_template("register.html", message="Please provide a password")
        elif len(password) < 9 or any((c in chars) for c in password):
            return render_template("register.html", message="Password must be 8 characters long and contain at least 1 number")
        retype = request.form.get("retype")
        if not retype:
            return render_template("register.html", message="Please retype password")
        if password != retype:
            return render_template("register.html", message="Both passwords must match")
        hashed = generate_password_hash(password)
        rows = db.execute("SELECT username FROM users")
        for row in rows:
            if row["username"] == username:
                return render_template("register.html", message="Username already taken")
            else:
                continue
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashed)
        return redirect("../login")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Select stocks to show in select dropdown
    stocks = db.execute("""SELECT * FROM transactions
                        WHERE user = :user""", user=session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)
    if request.method == "POST":
        symbol = str.upper(request.form.get("symbol"))
        if not symbol:
            return apology("missing symbol")
        quote = lookup(symbol)
        sell = int(request.form.get("shares"))

        rows = db.execute("""SELECT shares FROM transactions
                            WHERE user = :user AND symbol = :symbol""", \
                            user=session["user_id"], symbol=symbol)
        shares = int(rows[0]["shares"])
        if sell > shares:
            return apology("too many shares")
        price = float(quote['price'])
        total = price * sell
        if sell == shares:
            db.execute("""DELETE FROM transactions WHERE user = :user
                       AND symbol = :symbol""", user=session["user_id"], symbol=symbol)
        else:
            db.execute("""UPDATE transactions
                       SET shares = shares - :sell WHERE user = :user
                       AND symbol = :symbol""", sell=sell, user=session["user_id"], symbol=symbol)
        db.execute("""INSERT INTO history (user, symbol, shares, price)
                   VALUES (:user, :symbol, :shares, :price)""", \
                   user=session["user_id"], symbol=symbol, shares=sell*(-1), price=price)
        db.execute("""UPDATE users SET cash = cash + :total WHERE id = :id""", \
                   id=session["user_id"], total=total)
        return redirect("/")
def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
