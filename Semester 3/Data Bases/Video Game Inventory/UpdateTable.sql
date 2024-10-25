-- Check Armor Enhancement Table
SELECT * FROM ARMOR_ENHANCEMENT
-- Update on Armor Enhancement
UPDATE ARMOR_ENHANCEMENT SET name = 'changed' WHERE name = 'Alpha Enchantment Stone'
-- 2 rows affected
UPDATE ARMOR_ENHANCEMENT SET name = 'changed' WHERE NOT name = 'changed'
-- all the other rows are affected
UPDATE ARMOR_ENHANCEMENT SET extra_defense = extra_defense + 5 WHERE extra_defense <= 10
-- 3 rows affected
UPDATE ARMOR_ENHANCEMENT SET name = 'changed2' WHERE name IS NOT NULL
-- every row changed, can't check for NULL since we check before adding a new entry, so we can't have NULL
-- Check Status Effect Table
SELECT * FROM STATUS_EFFECT
--Update on Status Effect
UPDATE STATUS_EFFECT SET extra_damage = 0 WHERE extra_damage BETWEEN 20 AND 30
-- 1 row affected
UPDATE STATUS_EFFECT SET name = 'changed3' WHERE name like 'T%'
--1 row affected
-- Check Player Stats Table
SELECT * FROM PLAYER_STATS
-- Update on Player Stats
UPDATE PLAYER_STATS SET strength = 1 WHERE strength = 13 OR strength = 20
-- 3 rows affected
UPDATE PLAYER_STATS SET luck = 100 WHERE strength <= 15
-- 8 rows affected