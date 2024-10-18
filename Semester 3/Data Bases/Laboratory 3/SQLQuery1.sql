CREATE TABLE ARMOR(
	id  INT PRIMARY KEY,
	name varchar(50),
	type varchar(50),
	defense INT
)

CREATE TABLE ARMOR_ENHNCEMENTS(
	id INT PRIMARY KEY,
	name varchar(50),
	extra_defense INT,
	armor_id INT FOREIGN KEY REFERENCES ARMOR(id)
)

-- Weapon Table
CREATE TABLE WEAPON(
	id INT PRIMARY KEY,
	name varchar(50),
	type varchar(50),
	stamina_drain INT
)
-- 1:n Relationship
CREATE TABLE STATUS_EFFECT(
	id INT PRIMARY KEY,
	name varchar(50),
	extra_damage INT,
	weapon_id INT FOREIGN KEY REFERENCES WEAPON(id)
)

CREATE TABLE SKILL(
		id INT PRIMARY KEY,
		power_up varchar(50),
		cooldown INT,
)

--1:1 relationship
CREATE TABLE PLAYER_STATS(
	id INT PRIMARY KEY,
	strength INT,
	dexterity INT,
	vitality INT,
	luck INT,
	rune INT,
)

--1:1 relationship
CREATE TABLE COMPANION(
	id INT PRIMARY KEY,
	name varchar(50),
	health INT,
	stamina INT,
	mana INT,
)

CREATE TABLE PLAYER(
	id INT PRIMARY KEY,
	companion_id INT UNIQUE FOREIGN KEY REFERENCES COMPANION(id),
	stats_id INT UNIQUE FOREIGN KEY REFERENCES PLAYER_STATS(id),
	name varchar(50),
	body_type varchar(50),
	health INT,
	stamina INT,
	mana INT,
)

--1:n Relationship
CREATE TABLE EQUIPMENT(
	player_id INT FOREIGN KEY REFERENCES PLAYER(id),
	armor_id INT FOREIGN KEY REFERENCES ARMOR(id),
	weapon_id INT FOREIGN KEY REFERENCES WEAPON(id),
)

--n:m relationship
CREATE TABLE KNOWN_SKILLS(
	player_id INT FOREIGN KEY REFERENCES PLAYER(id),
	skill_id INT FOREIGN KEY REFERENCES SKILL(id),
)

CREATE TABLE ITEM(
	id INT PRIMARY KEY,
	name varchar(50),
	effect varchar(50),
)

--n:m relationship
CREATE TABLE OWNED_ITEM(
	player_id INT FOREIGN KEY REFERENCES PLAYER(id),
	item_id  INT FOREIGN KEY REFERENCES ITEM(id),
)
