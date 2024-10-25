CREATE TABLE ARMOR_SET(
	id  INT PRIMARY KEY CHECK (id>=0),
	name varchar(50) NOT NULL,
	type varchar(50) NOT NULL,
	defense INT DEFAULT 0 CHECK (defense>=0)
)

CREATE TABLE ARMOR_ENHANCEMENT(
	id INT PRIMARY KEY CHECK (id>=0),
	name varchar(50) NOT NULL,
	extra_defense INT DEFAULT 0 CHECK(extra_defense>0),
	armor_id INT FOREIGN KEY REFERENCES ARMOR_SET(id) CHECK(armor_id>=0)
)

-- Weapon Table
CREATE TABLE WEAPON(
	id INT PRIMARY KEY, CHECK (id>=0),
	name varchar(50) NOT NULL,
	type varchar(50) NOT NULL,
	stamina_drain INT DEFAULT 5 CHECK(stamina_drain>0)
)
-- 1:n Relationship
CREATE TABLE STATUS_EFFECT(
	id INT PRIMARY KEY, CHECK (id>=0),
	name varchar(50) NOT NULL,
	extra_damage INT DEFAULT 0 CHECK(extra_damage>=0),
	weapon_id INT FOREIGN KEY REFERENCES WEAPON(id) CHECK (weapon_id>=0)
)

CREATE TABLE SKILL(
		id INT PRIMARY KEY, CHECK (id>=0),
		power_up varchar(50) NOT NULL,
		cooldown INT DEFAULT 30 CHECK(cooldown>=0), 
)

--1:1 relationship
CREATE TABLE PLAYER_STATS(
    id INT PRIMARY KEY CHECK (id >= 0),
    strength INT DEFAULT 7 CHECK (strength >= 0),
    dexterity INT DEFAULT 7 CHECK (dexterity >= 0),
    vitality INT DEFAULT 7 CHECK (vitality >= 0),
    luck INT DEFAULT 7 CHECK (luck >= 0),
    rune INT DEFAULT 7 CHECK (rune >= 0)
)

--1:1 relationship
CREATE TABLE COMPANION(
    id INT PRIMARY KEY CHECK (id >= 0),
    name VARCHAR(50) NOT NULL,
    health INT DEFAULT 80 CHECK (health >= 0),
    stamina INT DEFAULT 60 CHECK (stamina >= 0),
    mana INT DEFAULT 40 CHECK (mana >= 0)
)

CREATE TABLE PLAYER(
    id INT PRIMARY KEY CHECK (id >= 0),
    companion_id INT UNIQUE,
    stats_id INT UNIQUE,
    name VARCHAR(50) NOT NULL,
    body_type VARCHAR(50) DEFAULT 'LIGHTWEIGHT',
    health INT DEFAULT 100 CHECK (health >= 0),
    stamina INT DEFAULT 70 CHECK (stamina >= 0),
    mana INT DEFAULT 50 CHECK (mana >= 0),
    FOREIGN KEY (companion_id) REFERENCES COMPANION(id),
    FOREIGN KEY (stats_id) REFERENCES PLAYER_STATS(id)
)

CREATE TABLE EQUIPMENT(
	player_id INT FOREIGN KEY REFERENCES PLAYER(id) CHECK (player_id>=0),
	armor_id INT FOREIGN KEY REFERENCES ARMOR_SET(id) CHECK (armor_id>=0),
	weapon_id INT FOREIGN KEY REFERENCES WEAPON(id) CHECK (weapon_id>=0),
)

--n:m relationship
CREATE TABLE KNOWN_SKILLS(
	player_id INT FOREIGN KEY REFERENCES PLAYER(id) CHECK (player_id>=0),
	skill_id INT FOREIGN KEY REFERENCES SKILL(id) CHECK (skill_id>=0),
)

CREATE TABLE ITEM(
	id INT PRIMARY KEY CHECK (id>=0),
	name varchar(50) NOT NULL,
	effect varchar(50) NOT NULL,
)

--n:m relationship
CREATE TABLE OWNED_ITEM(
	player_id INT FOREIGN KEY REFERENCES PLAYER(id) CHECK(player_id>=0),
	item_id  INT FOREIGN KEY REFERENCES ITEM(id) CHECK(item_id>=0),
)
