--Check data from Skill Table
SELECT * FROM SKILL
--Alter char for the power_up column
ALTER TABLE SKILL ALTER COLUMN power_up VARCHAR(150)
--Insert data into Skill Table --> Baldur Gate 3
INSERT INTO SKILL(id, power_up, cooldown) VALUES (0, 'Improves Shove, resistance to Shove, and Jumping', 120)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (1, 'Deduce the location of a hidden object, discern from the appearance of a wound what kind of weapon dealt it', 300)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (2, 'Recall lore about spells , magic items, the planes of existence, and the inhabitants of those planes', 500)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (3, 'Recall lore about historical events, legendary people, ancient kingdoms and lost civilizations', 500)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (4, 'Recall lore about deities, rites and prayers, holy symbols, and the practices of secret cults', 500)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (5, 'Recall lore about terrain, plants and animals, the weather, and natural cycles', 500)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (6, 'Act of legerdemain or manual trickery, such as planting something on someone else or concealing an object on your person', 180)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (7, 'Attempt to conceal yourself from enemies, slink past guards, slip away without being noticed, or sneak up on someone without being seen or heard', 50)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (8, 'Attempt to determine the true intentions of a creature', 750)
INSERT INTO SKILL(id, power_up, cooldown) VALUES (9, 'Delight an audience with music, dance, acting, storytelling, or some other form of entertainment', 600)
--Try to insert wrong values
INSERT INTO SKILL(id, power_up, cooldown) VALUES (-1, NULL, -1) -- Fails first on id
--Check data from Companion Table
SELECT * FROM COMPANION
--Input data into Companion Table
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (0, 'Maria', 10, 50, 0) -- Silent Hill 2
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (1, 'Cirilla', 150, 120, 70) -- Witcher Series
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (2, 'Asterion', 80, 120, 40) -- Baldur Gate 3
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (3, 'Shadowheart', 70, 90, 120)
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (4, 'Lae''zel', 130, 110, 25)
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (5, 'Ghost', 100, 90, 0) -- Call of Duty: Modern Warfare
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (6, 'Yuna', 70, 80, 0) -- Ghost of Tsushima
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (7, 'Atreus', 90, 90, 40) -- God of War
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (8, 'Yukari Takeba', 80, 60, 110) -- Persona 3
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (9, 'Mimic Tear', 100, 100, 100) -- Elden Ring
--Try to insert null name, error
INSERT INTO COMPANION(id, name, health, stamina, mana) VALUES (10, NULL, 0, 0, 0)
--Check data from Armor Set
SELECT * FROM ARMOR_SET
--Input data into Armor Set
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (0, 'Regular clothes', 'Light', 0)
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (1, 'Tantric Oath R', 'Light', 34) -- Persona 5
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (2, 'Godly Robe', 'Light', 38) -- Persona 4
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (3, 'Steinbjorn', 'Heavy', 77) -- God of War : Ragnarok
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (4, 'Winterized T-51B Power Armor', 'Heavy', 155) -- Fallout 3
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (5, 'Sakai Clan', 'Heavy', 68) -- Ghost of Tsushima
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (6, 'Diamond', 'Heavy', 80) -- Minecraft
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (7, 'Into the Spider-Verse', 'Light', 45) -- Marvel's Spider-man
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (8, 'Fallen Knight', 'Light', 48) -- Dark Souls 3
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (9, 'Wolf', 'Light', 27) -- Sekiro : Shadow Die Twice
--Try to insert null type, error
INSERT INTO ARMOR_SET(id, name, type, defense) VALUES (10, 'name', NULL, 23)
--Check data from Armor Enhancement Table
SELECT * FROM ARMOR_ENHANCEMENT
--Input data into Armor Enhancement Table --> Aion
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (0, 'Alpha Enchantment Stone', 5, 9)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (1, 'Beta Enchantment Stone', 10, 5)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (2, 'Gamma Enchantment Stone', 15, 5)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (3, 'Delta Enchantment Stone', 20, 3)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (4, 'Epsilon Enchantment Stone', 25, 2)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (5, 'Omega Enchantment Stone', 30, 1)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (6, 'Gamma Enchantment Stone', 15, 2)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (7, 'Gamma Enchantment Stone', 15, 6)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (8, 'Alpha Enchantment Stone', 5, 7)
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (9, 'Omega Enchantment Stone', 30, 5)
--Try to insert negative value for defense, error
INSERT INTO ARMOR_ENHANCEMENT(id, name, extra_defense, armor_id) VALUES (10, 'Alpha Enchantment Stone', -1, 9)
--Check data from Weapon Table
SELECT * FROM WEAPON
--Add damage to Weapon Table
ALTER TABLE WEAPON ADD damage INT CHECK(damage>=0)
--Input data into Weapon Table
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (0, 'Handgun', 'Ranged', 5, 60)
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (1, 'Metal Pipe', 'Melee', 22, 31) -- Silent Hill 2
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (2, 'Chainsaw', 'Melee', 10, 86) -- The Forest
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (3, 'Iron Sword', 'Melee', 15, 45) -- Minecraft
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (4, 'Stormflash Loong Staff', 'Melee', 5, 24) -- Black Myth:Wukong
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (5, 'Combat Knife', 'Melee', 13, 29) -- Resident Evil 2
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (6, 'Lancaster Repeater', 'Ranged', 11, 48) -- Red Dead Redemption 2
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (7, 'Avelyn', 'Ranged', 28, 37) -- Dark Souls 2
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (8, 'Greatsword of Artorias', 'Melee', 42, 54) -- Dark Souls
INSERT INTO WEAPON(id, name, type, stamina_drain, damage) VALUES (9, 'Dragonbone Bow', 'Ranged', 24, 33) -- Elder Scrolls V : Skyrim
--Check data from Status Effect
SELECT * FROM STATUS_EFFECT
--Input data into Status Effect Table --> Monster Hunter : World
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (0, 'Fire', 13, 3)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (1, 'Water', 7, 4)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (2, 'Thunder', 15, 7)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (3, 'Ice', 9, 9)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (4, 'Dragon', 11, 8)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (5, 'Poison', 2, 3)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (6, 'Stun', 0, 1)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (7, 'Paralysis', 0, 0)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (8, 'Sleep', 0, 7)
INSERT INTO STATUS_EFFECT(id, name, extra_damage, weapon_id) VALUES (9, 'Blast', 20, 9)
--Check data from Player Stats
SELECT * FROM PLAYER_STATS
--Input data into Player Stats table
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (0, 17, 11, 13, 7, 12)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (1, 13, 12, 15, 11, 10)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (2, 19, 11, 14, 12, 7)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (3, 8, 15, 17, 14, 14)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (4, 10, 8, 18, 16, 11)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (5, 13, 7, 12, 19, 9)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (6, 7, 7, 20, 16, 15)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (7, 20, 20, 12, 8, 14)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (8, 14, 13, 14, 10, 20)
INSERT INTO PLAYER_STATS(id, strength, dexterity, vitality, luck, rune) VALUES (9, 8, 11, 15, 20, 3)
--Check data from Item
SELECT * FROM ITEM
--Alter length of effect
ALTER TABLE ITEM ALTER COLUMN effect varchar(100)
--Input data into Item --> Sekiro : Shadows Die Twice
INSERT INTO ITEM(id, name, effect) VALUES (0, 'Ako''Sugar', 'Temporarily boosts Vitality damage dealt')
INSERT INTO ITEM(id, name, effect) VALUES (1, 'Bell Demon', 'Increases difficulty but also increases items drop rates')
INSERT INTO ITEM(id, name, effect) VALUES (2, 'Bulging Coin Purse', '1000 Sen')
INSERT INTO ITEM(id, name, effect) VALUES (3, 'Bundled Jizo Statue', 'Allows self-revive')
INSERT INTO ITEM(id, name, effect) VALUES (4, 'Contact Medicine', 'Inflicts a weak poison on oneself, thus warding off more dangerous poisoning')
INSERT INTO ITEM(id, name, effect) VALUES (5, 'Dousing Powder', 'Heals status abnormality "Burn" and provides resistance to it')
INSERT INTO ITEM(id, name, effect) VALUES (6, 'Fine Snow', 'Gradually recovers Vitality for a time')
INSERT INTO ITEM(id, name, effect) VALUES (7, 'Gachiin''s Sugar', 'Silences and conceals the user, making it difficult for their enemies to find them')
INSERT INTO ITEM(id, name, effect) VALUES (8, 'Healing Gourd', 'Restores the user''s Health')
INSERT INTO ITEM(id, name, effect) VALUES (9, 'Homeward Idol', 'Returns the user to the last safe zone')
--Check data from Player
SELECT * FROM PLAYER
--Input data into Player Table
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (0, 0, 4, 'James Sunderland', 'Lightweight', 80, 50, 0) -- Silent Hill 2
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (1, 1, 7, 'Geralt of Rivia', 'Heavyweight', 80, 70, 50) -- Witcher Series
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (2, 3, 2, 'Taz', 'Heavyweight', 90, 80, 15) -- Baldur Gate 3
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (3, 5, 9, 'Price', 'Athletic', 80, 90, 0) -- Call of Duty : Modern Warfare
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (4, 6, 1, 'Jin Sakai', 'Heavyweight', 85, 80, 0) -- Ghost of Tsushima
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (5, 7, 8, 'Kratos', 'Heavyweight', 90, 100, 0) -- God of War
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (6, 8, 3, 'Makoto Yuki', 'Lightweight', 75, 60, 110) -- Persona 3
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (7, 9, 0, 'Tarnished', 'Lightweight', 90, 70, 50) -- Elden Ring
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (8, 2, 5, 'Jonathan E.Reid', 'Lightweight', 88, 100, 0) -- Vampyrez
INSERT INTO PLAYER(id, companion_id, stats_id, name, body_type, health, stamina, mana) VALUES (9, 4, 6, 'Jack the Ripper', 'Cyborg', 95, 130, 0) -- Metal Gear Rising : Revengence
--Check data from Equipment
SELECT * FROM EQUIPMENT
--Input data into Equipment
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (0, 0, 1)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (0, 0, 0)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (0, 0, 2)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (1, 1, 3)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (2, 2, 4)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (2, 4, 8)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (3, 9, 6)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (4, 5, 5)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (5, 3, 8)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (6, 7, 9)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (7, 6, 7)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (7, 8, 7)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (8, 9, 0)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (8, 9, 5)
INSERT INTO EQUIPMENT(player_id, armor_id, weapon_id) VALUES (9, 2, 3)
--Check data from Known Skills
SELECT* FROM KNOWN_SKILLS
--Input data into Known Skills
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (0, 1)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (0, 3)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (0, 4)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (1, 0)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (1, 1)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (1, 2)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (1, 5)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (1, 8)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (2, 9)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (2, 6)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (2, 7)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (3, 7)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (4, 7)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (4, 1)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (4, 6)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (5, 3)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (5, 4)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (5, 5)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (6, 6)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (6, 7)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (7, 9)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (8, 0)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (8, 8)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (8, 7)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (9, 9)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (9, 0)
INSERT INTO KNOWN_SKILLS(player_id, skill_id) VALUES (9, 6)
--Check data from Owned Items
SELECT * FROM OWNED_ITEM
--Input data into Owned Item
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (0, 1)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (0, 8)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (1, 0)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (1, 2)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (2, 9)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (2, 3)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (2, 4)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (2, 5)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (3, 6)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (4, 4)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (4, 7)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (5, 1)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (5, 3)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (5, 8)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (6, 1)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (6, 6)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (7, 1)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (7, 9)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (8, 7)
INSERT INTO OWNED_ITEM(player_id, item_id) VALUES (9, 1)

