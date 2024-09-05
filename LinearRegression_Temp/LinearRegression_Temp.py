from scipy import stats
import pandas as pd

file_path = 'data.xlsx'
df = pd.read_excel(file_path)

x_data = df.iloc[:, 0].values
y_data = df.iloc[:, 1].values

slope, intercept, r_value, p_value, std_err = stats.linregress(x_data, y_data)

print(f"LinearFittingFormula: y = {slope:.4f} * x + {intercept:.4f}")
print(x_data)
print(y_data)

