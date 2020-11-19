import tkinter as t

window = None
display_label = None
expression = ''


def press(num):
    global expression

    if num == 'c':
        expression = ''

    elif num == 'b':
        expression = expression[:-1]

    elif num == '=':
        expression = expression.replace('×', '*')
        expression = expression.replace('÷', '/')

        print(expression)

        try:
            total = str(eval(expression))[0:16]

        except:
            total = 'error  '

        display_label['text'] = total
        expression = ''

        return

    else:
        expression = expression + str(num)

    display_label['text'] = expression


def setup_GUI():
    global window
    global display_label

    window = t.Tk()
    window.title('myCalc')
    window.resizable(width=0, height=0)

    display_label = t.Label(window, text='', anchor='e', relief=t.SUNKEN, width=15, font='Arial 20')
    display_label.grid(row=0, column=0, columnspan=4, padx=10, pady=10)

    btn1 = t.Button(window, text=str(1), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(1))
    btn2 = t.Button(window, text=str(2), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(2))
    btn3 = t.Button(window, text=str(3), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(3))
    btn4 = t.Button(window, text=str(4), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(4))
    btn5 = t.Button(window, text=str(5), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(5))
    btn6 = t.Button(window, text=str(6), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(6))
    btn7 = t.Button(window, text=str(7), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(7))
    btn8 = t.Button(window, text=str(8), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(8))
    btn9 = t.Button(window, text=str(9), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(9))
    btn0 = t.Button(window, text=str(0), width=5, height=2, bg='gray', fg='white', font='Arial 15',
                    command=lambda: press(0))

    btn1.grid(row=2, column=0)
    btn2.grid(row=2, column=1)
    btn3.grid(row=2, column=2)
    btn4.grid(row=3, column=0)
    btn5.grid(row=3, column=1)
    btn6.grid(row=3, column=2)
    btn7.grid(row=4, column=0)
    btn8.grid(row=4, column=1)
    btn9.grid(row=4, column=2)
    btn0.grid(row=5, column=1)

    clearBtn = t.Button(window, text='C', width=5, height=1, bg='orange', fg='red',
                        font='Arial 15', command=lambda: press('c'))
    backspaceBtn = t.Button(window, text='＜', width=5, height=1, bg='orange', fg='black',
                            font='Arial 15', command=lambda: press('b'))
    modBtn = t.Button(window, text='％', width=5, height=1, bg='orange', fg='black',
                      font='Arial 15', command=lambda: press('%'))
    squareBtn = t.Button(window, text='X²', width=5, height=1, bg='orange', fg='black',
                         font='Arial 15', command=lambda: press('**2'))
    addBtn = t.Button(window, text='+', width=5, height=2, bg='orange', fg='gray',
                      font='Arial 15', command=lambda: press('+'))
    subBtn = t.Button(window, text='-', width=5, height=2, bg='orange', fg='gray',
                      font='Arial 15', command=lambda: press('-'))
    mulBtn = t.Button(window, text='×', width=5, height=2, bg='orange', fg='gray',
                      font='Arial 15', command=lambda: press('×'))
    divBtn = t.Button(window, text='÷', width=5, height=2, bg='orange', fg='gray',
                      font='Arial 15', command=lambda: press('÷'))
    resultBtn = t.Button(window, text='=', width=5, height=2, bg='orange', fg='black',
                         font='Arial 15', command=lambda: press('='))
    dotBtn = t.Button(window, text='ㆍ', width=5, height=2, bg='orange', fg='black',
                      font='Arial 15', command=lambda: press('.'))

    clearBtn.grid(row=1, column=0)
    backspaceBtn.grid(row=1, column=1)
    modBtn.grid(row=1, column=2)
    squareBtn.grid(row=1, column=3)
    addBtn.grid(row=2, column=3)
    subBtn.grid(row=3, column=3)
    mulBtn.grid(row=4, column=3)
    divBtn.grid(row=5, column=3)
    resultBtn.grid(row=5, column=2)
    dotBtn.grid(row=5, column=0)


setup_GUI()
window.mainloop()
