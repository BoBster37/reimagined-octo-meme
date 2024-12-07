import sqlite3
con = sqlite3.connect('baza.db')
con.row_factory = sqlite3.Row
cur = con.cursor()
def create():
    cur.execute("""
    CREATE TABLE IF NOT EXISTS produkt (
    id INTEGER PRIMARY KEY ASC,
    nazwa varchar(250) NOT NULL,
    opis varchar(250) NOT NULL,
    cena real NOT NULL,
    ilosc integer NOT NULL
    )""")
    print("Table Produkt was created")

def add_product(name, description, price, amount):
    cur.execute('''
        INSERT INTO produkt
        VALUES (NULL, ?, ?, ?, ?)
    ''', (name, description, price, amount))
    con.commit()
    print("New record was added")

def find_product(parameter):

    if type(parameter) == int:
        cur.execute('''
        select * from produkt 
        where id = ?
         ''', (parameter,))

    if type(parameter) == str:
        cur.execute('''
        select * from produkt 
        where nazwa = ?
         ''', (parameter,))

    products = cur.fetchall()
    if len(products) == 0:
        print("No records were found")
    else:
        for product in products:
            print(product['id'], product['nazwa'], product['opis'], product['cena'], product['ilosc'])

def update_product(id, name, description, price, amount):
    cur.execute('''
    UPDATE produkt set nazwa = ?, opis = ?, cena = ?, ilosc = ?
    where id = ?
    ''', (name, description, price, amount, id))
    con.commit()
    print("Record was updated")

def find_all():
    cur.execute('''
    SELECT * FROM produkt
    ''')
    products = cur.fetchall()
    if len(products) == 0:
        print("No records were found")
    else:
        for product in products:
            print(product['id'], product['nazwa'], product['opis'], product['cena'], product['ilosc'])

def delete_product(id):
    cur.execute('''
    DELETE FROM produkt WHERE id = ?
    ''', (id,))
    con.commit()
    print("Record was deleted")




