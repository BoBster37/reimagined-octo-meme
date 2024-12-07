import sqlite3
con = sqlite3.connect('baza2.db')
con.row_factory = sqlite3.Row
cur = con.cursor()
cur.execute("DROP TABLE IF EXISTS pokoj;")

cur.execute("""    
            CREATE TABLE IF NOT EXISTS pokoj (     
                id INTEGER PRIMARY KEY ASC,
                nr_pokoju varchar(250) NOT NULL   
                )""")

cur.executescript("""    
                    DROP TABLE IF EXISTS gosc;    
                    CREATE TABLE IF NOT EXISTS gosc (        
                    id INTEGER PRIMARY KEY ASC,        
                    imie varchar(250) NOT NULL,        
                    nazwisko varchar(250) NOT NULL,        
                    pokoj_id INTEGER NOT NULL,        
                    FOREIGN KEY(pokoj_id) REFERENCES pokoj(id)    
                    )""")

cur.executescript("""    
                    DROP TABLE IF EXISTS uwagi;    
                    CREATE TABLE IF NOT EXISTS uwagi (        
                    id INTEGER PRIMARY KEY ASC,
                    uwaga varchar(250) NOT NULL,            
                    gosc_id INTEGER NOT NULL,        
                    FOREIGN KEY(gosc_id) REFERENCES gosc(id)    
                    )""")

cur.execute('INSERT INTO pokoj VALUES(NULL, ?);', ('1408',))
cur.execute('INSERT INTO pokoj VALUES(NULL, ?);', ('1409',))
cur.execute('INSERT INTO pokoj VALUES(NULL, ?);', ('1410',))


con.close()
