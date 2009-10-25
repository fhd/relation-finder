DROP TABLE IF EXISTS buddys;

CREATE TABLE buddys (
	owner_nr integer NOT NULL,
	buddy_nr integer NOT NULL,
	CONSTRAINT buddys_pkey
	PRIMARY KEY (owner_nr, buddy_nr)
) WITHOUT OIDS;

CREATE INDEX buddy ON buddys USING btree (buddy_nr);
CREATE INDEX buddy_owner ON buddys USING btree (owner_nr, buddy_nr);
CREATE UNIQUE INDEX buddys_pkey ON buddys USING btree (owner_nr, buddy_nr);

INSERT INTO buddys (owner_nr, buddy_nr) VALUES (1, 2);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (1, 3);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (2, 1);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (2, 4);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (3, 1);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (3, 6);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (4, 2);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (4, 5);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (4, 6);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (5, 4);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (6, 3);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (6, 4);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (6, 7);
INSERT INTO buddys (owner_nr, buddy_nr) VALUES (7, 6);
