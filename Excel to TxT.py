import openpyxl
import csv
import pandas as pd
x1 = pd.ExcelFile('zoomexcel.xlsx')
x1.sheet_names
['Information']
for sheet in x1.sheet_names:
    file = pd.read_excel(x1, sheet_name=sheet)
    file.to_csv(sheet+'.txt',header = False, index= False, encoding = "ANSI")
