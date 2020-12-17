from tkinter import *
from tkinter import messagebox

window = None


def setupGUI():
    global window
    window = Tk()
    window.title("final exam")

    title_label = Label(window, text="Talk Box", font="Arial 14 bold", width="30")
    title_label.grid(row=0, column=1, padx=10, pady=10)

    yes_no_button = Button(window, text="Click me", font="Arial 14 bold", width=15, height=2, command=yesNoDialog)
    yes_no_button.grid(row=1, column=1, padx=3, pady=3)


def yesNoDialog():
    ans = messagebox.askyesno('question', '당신은 고대인 입니까?')
    if ans:
        messagebox.showinfo('와우', '저는 현대인 입니다.')
    else:
        messagebox.showinfo("ㅠㅠ", "저는 고대인 입니다.")


setupGUI()
window.mainloop()
