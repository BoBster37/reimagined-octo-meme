

-- tables
-- Table: cafe
CREATE TABLE cafe (
    id int  NOT NULL,
    name varchar(20)  NOT NULL,
    Adres varchar(20)  NOT NULL,
    CONSTRAINT cafe_pk PRIMARY KEY  (id)
);

-- Table: delv
CREATE TABLE delv (
    supp_id int  NOT NULL,
    cafe_id int  NOT NULL,
    CONSTRAINT delv_pk PRIMARY KEY  (supp_id,cafe_id)
);

-- Table: dish
CREATE TABLE dish (
    id int  NOT NULL,
    name varchar(15)  NOT NULL,
    CONSTRAINT dish_pk PRIMARY KEY  (id)
);

-- Table: emp
CREATE TABLE emp (
    id int  NOT NULL,
    name varchar(15)  NOT NULL,
    sname varchar(15)  NOT NULL,
    pensja numeric(10,2)  NOT NULL,
    post_id int  NOT NULL,
    cafe_id int  NOT NULL,
    CONSTRAINT emp_pk PRIMARY KEY  (id)
);

-- Table: post
CREATE TABLE post (
    id int  NOT NULL,
    name varchar(10)  NOT NULL,
    CONSTRAINT post_pk PRIMARY KEY  (id)
);

-- Table: sales
CREATE TABLE sales (
    cena numeric(10,2)  NOT NULL,
    dish_id int  NOT NULL,
    cafe_id int  NOT NULL,
    CONSTRAINT sales_pk PRIMARY KEY  (dish_id,cafe_id)
);

-- Table: supp
CREATE TABLE supp (
    id int  NOT NULL,
    name varchar(20)  NOT NULL,
    Adres varchar(20)  NOT NULL,
    CONSTRAINT supp_pk PRIMARY KEY  (id)
);

-- foreign keys
-- Reference: Dostawa_Dostawca (table: delv)
ALTER TABLE delv ADD CONSTRAINT Dostawa_Dostawca
    FOREIGN KEY (supp_id)
    REFERENCES supp (id);

-- Reference: Dostawa_Restauracja (table: delv)
ALTER TABLE delv ADD CONSTRAINT Dostawa_Restauracja
    FOREIGN KEY (cafe_id)
    REFERENCES cafe (id);

-- Reference: Pracownik_Restauracja (table: emp)
ALTER TABLE emp ADD CONSTRAINT Pracownik_Restauracja
    FOREIGN KEY (cafe_id)
    REFERENCES cafe (id);

-- Reference: Pracownik_Stanowisko (table: emp)
ALTER TABLE emp ADD CONSTRAINT Pracownik_Stanowisko
    FOREIGN KEY (post_id)
    REFERENCES post (id);

-- Reference: Sprzedaz_Danie (table: sales)
ALTER TABLE sales ADD CONSTRAINT Sprzedaz_Danie
    FOREIGN KEY (dish_id)
    REFERENCES dish (id);

-- Reference: Sprzedaz_Restauracja (table: sales)
ALTER TABLE sales ADD CONSTRAINT Sprzedaz_Restauracja
    FOREIGN KEY (cafe_id)
    REFERENCES cafe (id);


