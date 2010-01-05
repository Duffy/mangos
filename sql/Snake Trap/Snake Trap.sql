-- apply poison triggering spells
DELETE FROM creature_template_addon WHERE entry IN (19921,19833);
INSERT INTO creature_template_addon VALUES
(19921,0,0,0,0,0,'34657 0'),
(19833,0,0,0,0,0,'6645 0');

-- make them friendly for each other that they won't attack at stats (player faction) apply
UPDATE creature_template SET faction_A = 35, faction_H = 35 WHERE entry IN (19833,19921);