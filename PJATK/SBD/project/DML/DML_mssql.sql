INSERT INTO post (id, name)
VALUES
(1,'chief'),
(2,'manager'),
(3,'cashier'),
(4,'cook');

INSERT INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES
(1,'Jason','Spears',3200,1,1),
(2,'Dominic','Caldwell',2600,2,1),
(3,'Daniel','Hawkins',2600,2,2),
(4,'Ahmed','Ryan',2600,2,3),
(5,'Katie','Hutchinson',1900,3,2),
(6,'Fiona','James',1900,3,3),
(7,'Dina','Walters',2120,4,1),
(8,'Maxim','Olson',2120,4,2);

INSERT INTO cafe (id, name, adres)
VALUES
(1,'Cafe','49 Alabama St'),
(2,'Bar','744 Patterson St'),
(3,'Coffee','1804 Winona St');

INSERT INTO supp (id,name,adres)
VALUES
(1,'Nissin Foods Group','1006 Cedar St'),
(2,'Tate & Lyle','12801 Susan St SW'),
(3,'Groupe Bel','2330 Briggs Ave'),
(4,'WhiteWave Foods','8934 Buckeye Rd');

INSERT INTO delv (supp_id,cafe_id)
VALUES
(1,1),
(1,3),
(2,1),
(3,2),
(2,3);

INSERT INTO sales (cena, dish_id, cafe_id)
VALUES
(4.0,3,2),
(3.5,2,2),
(2.0,2,3),
(7.4,4,1),
(6.0,1,1),
(1.5,5,3);

INSERT INTO dish (id,name)
VALUES
(1,'Ham Sandwich'),
(2,'Latte'),
(3,'Mojito'),
(4,'Omelette');
(5,'Green Tea');
