/* Query that returns the average energy of songs that are by Drake */
SELECT AVG(energy) FROM songs WHERE artist_Id IN (SELECT id FROM artists WHERE name = "Drake");