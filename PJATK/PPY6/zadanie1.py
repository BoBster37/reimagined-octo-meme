import tkinter

class MyGUI:
    def init(self):
        self.main_window = tkinter.Tk()
        self.label1 = tkinter.Label(self.main_window, text = 'Helo')
        self.label2 = tkinter.Label(self.main_window, text = 'World')

        self.label1.pack(side='left')
        self.label2.pack(side='left')

        tkinter.mainloop()


gui = MyGUI()