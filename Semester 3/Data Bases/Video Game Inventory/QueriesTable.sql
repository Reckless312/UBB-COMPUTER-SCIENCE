-- a)
-- Find every player and companion
SELECT name FROM PLAYER UNION SELECT name FROM COMPANION
-- Find every player and some companions
SELECT name FROM PLAYER UNION SELECT name FROM COMPANION WHERE name LIKE 'Y%' OR health >= 75

-- b) 
-- Find every player and companion who share the same amount of health
SELECT id, name, health FROM PLAYER WHERE health IN (
SELECT health FROM PLAYER INTERSECT SELECT health FROM COMPANION)
UNION
SELECT id, name, health FROM COMPANION WHERE health IN (
SELECT health FROM PLAYER INTERSECT SELECT health FROM COMPANION)
ORDER BY health
-- Find every player and companion who share the same amount of stamina
SELECT id, name, stamina FROM PLAYER WHERE stamina IN (
SELECT stamina FROM PLAYER INTERSECT SELECT stamina FROM COMPANION)
UNION
SELECT id, name, stamina FROM COMPANION WHERE stamina IN (
SELECT stamina FROM PLAYER INTERSECT SELECT stamina FROM COMPANION)
ORDER BY stamina

-- c) 
-- Find the players who have a different value of mana than all of the companions
SELECT id, name, mana FROM PLAYER WHERE mana IN (
SELECT mana FROM PLAYER EXCEPT SELECT mana from COMPANION)

-- Find the armors that don't have any enhancements on them
SELECT name, type, defense, defense / 5 + 2.5 AS damage_reduction FROM ARMOR_SET WHERE id NOT IN (
SELECT armor_id FROM ARMOR_ENHANCEMENT)

-- d)
-- Find all the skills even if no player knows them
-- No data in the table to check so we add it
INSERT INTO SKILL (id, power_up, cooldown) VALUES (11, 'test', 50)

SELECT SKILL.power_up, PLAYER.name FROM SKILL
LEFT JOIN KNOWN_SKILLS ON KNOWN_SKILLS.skill_id = SKILL.id
LEFT JOIN PLAYER ON KNOWN_SKILLS.player_id = PLAYER.id

-- The other way around
SELECT PLAYER.name, SKILL.power_up FROM PLAYER
RIGHT JOIN KNOWN_SKILLS ON KNOWN_SKILLS.player_id = PLAYER.id
RIGHT JOIN SKILL ON KNOWN_SKILLS.skill_id = SKILL.id

-- Delete the new added entry
DELETE FROM SKILL WHERE id = 11

-- Find for each player the armors that they have and the skills
SELECT DISTINCT PLAYER.name, ARMOR_SET.name, ARMOR_SET.defense, SKILL.power_up
FROM PLAYER
INNER JOIN EQUIPMENT ON EQUIPMENT.player_id = PLAYER.id
INNER JOIN ARMOR_SET ON EQUIPMENT.armor_id = ARMOR_SET.id
INNER JOIN KNOWN_SKILLS ON KNOWN_SKILLS.player_id = PLAYER.id
INNER JOIN SKILL ON SKILL.id = KNOWN_SKILLS.skill_id

-- Show everything from the player and armor
SELECT * FROM PLAYER
FULL JOIN EQUIPMENT ON EQUIPMENT.player_id = PLAYER.id
FULL JOIN ARMOR_SET ON ARMOR_SET.id = EQUIPMENT.armor_id

-- e) Find the players that don't have the armor that fits the required conditions

SELECT id, name FROM PLAYER WHERE id IN (SELECT DISTINCT player_id FROM EQUIPMENT WHERE armor_id NOT IN (SELECT TOP 5 id FROM ARMOR_SET WHERE id IN (
SELECT id FROM ARMOR_ENHANCEMENT WHERE extra_defense NOT BETWEEN 15 AND 25)
OR defense <=50))
ORDER BY name

-- Find all the owned items from the players
SELECT id, name, effect FROM ITEM WHERE id IN(
SELECT item_id FROM OWNED_ITEM)

-- f)

INSERT INTO SKILL (id, power_up, cooldown) VALUES (11, 'test', 50)

-- Retrieve first 5 skills that are assigned to a player
SELECT TOP 5 SKILL.id, SKILL.power_up FROM SKILL WHERE EXISTS (
SELECT KNOWN_SKILLS.skill_id FROM KNOWN_SKILLS WHERE KNOWN_SKILLS.skill_id = SKILL.id)

-- Retrieve all the skills that are NOT assigned to a player
SELECT SKILL.id, SKILL.power_up FROM SKILL WHERE NOT EXISTS (
SELECT KNOWN_SKILLS.skill_id FROM KNOWN_SKILLS WHERE KNOWN_SKILLS.skill_id = SKILL.id)

DELETE FROM SKILL WHERE id = 11

-- g) Retrieve the player table as a "data" in the from clause and return only specific names

SELECT name FROM (SELECT id, name FROM PLAYER WHERE health >= 50 AND stamina <=80) AS data
WHERE name LIKE 'J%' OR name LIKE 'T%'

-- Retrieve the name of the armor that fits the expression in term of defense
SELECT name FROM (SELECT name FROM ARMOR_SET WHERE defense + 10 >= 50) AS data

-- h) 
-- Find the player's healths that fit the criteria
SELECT health, COUNT(*) AS health FROM PLAYER
GROUP BY health
HAVING health >=80 AND health <=90

-- Returns the id of the players who have more skills than the player with the least amount of items
SELECT player_id FROM KNOWN_SKILLS GROUP BY player_id
HAVING COUNT(skill_id) > ( SELECT MIN(item_owned) FROM (
SELECT COUNT(*) AS item_owned FROM OWNED_ITEM
GROUP BY player_id) AS items)

-- Returns the id of the players who have more health than the avg of the companions in total health
SELECT id FROM PLAYER GROUP BY id
HAVING AVG(health) > (SELECT AVG(health) FROM COMPANION)

-- Returns the id of the players who have more stamina than all of the companions
SELECT id FROM PLAYER
WHERE stamina > (SELECT MAX(stamina) FROM COMPANION)
GROUP BY id

-- Returns the stamina "groups" who in total give more than a 100, there are more players with the same values
SELECT stamina FROM PLAYER GROUP BY stamina
HAVING SUM(stamina) > 100

-- i)

-- Return the player that have the strength status bigger than 10
SELECT id FROM PLAYER WHERE stats_id = ANY (SELECT id FROM PLAYER_STATS WHERE PLAYER_STATS.strength > 10)
-- Rewrite it with IN
SELECT id FROM PLAYER WHERE stats_id IN (SELECT id FROM PLAYER_STATS WHERE strength > 10)
-- Return the player_id who have a weapon with more than 50 damage
SELECT DISTINCT player_id FROM EQUIPMENT WHERE weapon_id = ANY (SELECT id FROM WEAPON WHERE WEAPON.damage >= 50)
-- Rewrite it
SELECT DISTINCT player_id FROM EQUIPMENT WHERE weapon_id IN (SELECT id FROM WEAPON WHERE damage >= 50)
-- Return the names of the companions who have more health than all the players
SELECT name FROM COMPANION WHERE health > ALL (SELECT health FROM PLAYER)
-- Rewrite it with aggregation operators
SELECT name FROM COMPANION WHERE health > (SELECT MAX(health) FROM PLAYER)
-- Return the names of the companions who have more mana than all the players
SELECT name FROM COMPANION WHERE mana > ALL (SELECT mana FROM PLAYER)
-- Rewrite it
SELECT name FROM COMPANION WHERE mana > (SELECT MAX(mana) FROM PLAYER)
