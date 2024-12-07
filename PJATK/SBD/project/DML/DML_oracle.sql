------------------- POST
INSERT ALL
INTO post (id, name)
VALUES (1,'chief')
INTO post (id, name)
VALUES (2,'manager')
INTO post (id, name)
VALUES (3,'cashier')
INTO post (id, name)
VALUES (4,'cook')
SELECT * FROM Dual;
------------------- EMP
INSERT ALL
INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES (1,'Jason','Spears',3200,1,1)
INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES (2,'Dominic','Caldwell',2600,2,1)
INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES (3,'Daniel','Hawkins',2600,2,2)
INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES (4,'Ahmed','Ryan',2600,2,3)
INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES (5,'Katie','Hutchinson',1900,3,2)
INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES (6,'Fiona','James',1900,3,3)
INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES (7,'Dina','Walters',2120,4,1)
INTO emp (id, name, sname, pensja, post_id, cafe_id)
VALUES (8,'Maxim','Olson',2120,4,2)
SELECT * FROM Dual;
------------------- CAFE
INSERT ALL
INTO cafe (id, name, adres)
VALUES (1,'Cafe','49 Alabama St')
INTO cafe (id, name, adres)
VALUES (2,'Bar','744 Patterson St')
INTO cafe (id, name, adres)
VALUES (3,'Coffee','1804 Winona St')
SELECT * FROM Dual;
------------------- SUPP
INSERT ALL
INTO supp (id, name, adres)
VALUES (1,'Nissin Foods Group','1006 Cedar St')
INTO supp (id, name, adres)
VALUES (2,'Tate & Lyle','12801 Susan St SW')
INTO supp (id, name, adres)
VALUES (3,'Groupe Bel','2330 Briggs Ave')
INTO supp (id, name, adres)
VALUES (4,'WhiteWave Foods','8934 Buckeye Rd')
SELECT * FROM Dual;
------------------- DELV
INSERT ALL
INTO delv (supp_id, cafe_id)
VALUES (1,1)
INTO delv (supp_id, cafe_id)
VALUES (1,3)
INTO delv (supp_id, cafe_id)
VALUES (2,1)
INTO delv (supp_id, cafe_id)
VALUES (3,2)
INTO delv (supp_id, cafe_id)
VALUES (2,3)
SELECT * FROM Dual;
------------------- SALES
INSERT ALL
INTO sales (cena, dish_id, cafe_id)
VALUES (4.0,3,2)
INTO sales (cena, dish_id, cafe_id)
VALUES (3.5,2,2)
INTO sales (cena, dish_id, cafe_id)
VALUES (2.0,2,3)
INTO sales (cena, dish_id, cafe_id)
VALUES (7.4,4,1)
INTO sales (cena, dish_id, cafe_id)
VALUES (6.0,1,1)
INTO sales (cena, dish_id, cafe_id)
VALUES (1.5,5,3)
SELECT * FROM Dual;
------------------- DISH
INSERT ALL
INTO dish (id,name)
VALUES (1,'Ham Sandwich')
INTO dish (id,name)
VALUES (2,'Latte')
INTO dish (id,name)
VALUES (3,'Mojito')
INTO dish (id,name)
VALUES (4,'Omelette')
INTO dish (id,name)
VALUES (5,'Green Tea')
SELECT * FROM Dual;
