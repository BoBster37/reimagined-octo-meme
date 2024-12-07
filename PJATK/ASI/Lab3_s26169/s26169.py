import pandas as pd
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.linear_model import Ridge
from sklearn.preprocessing import StandardScaler, OneHotEncoder, PolynomialFeatures
from sklearn.compose import ColumnTransformer
from sklearn.model_selection import train_test_split, RepeatedKFold, cross_val_score
from sklearn.pipeline import Pipeline
from sklearn.metrics import r2_score, mean_absolute_error, mean_squared_error
import matplotlib.pyplot as plt

# Parametry do trenowania
test_size = 0.2  # Wielkość zbioru testowego
random_state = 42  # Ziarno losowe dla powtarzalności wyników


data = pd.read_csv('CollegeDistance.csv')
data = data.drop(columns=['rownames']) 

# Rozdzielenie danych na cechy (X) i zmienną zależną (y)
X = data.drop(columns=['score'])
y = data['score']

# Tworzenie ColumnTransformer, aby zastosować różne przetwarzanie do kolumn liczbowych i kategorycznych
numeric_features = ['unemp', 'wage', 'distance', 'tuition', 'education']
categorical_features = ['gender', 'ethnicity', 'fcollege', 'mcollege', 'home', 'urban', 'income', 'region']

# Przekształcanie danych liczbowych i kategorycznych
preprocessor = ColumnTransformer(
    transformers=[
        ('num', StandardScaler(), numeric_features),  # Standaryzacja dla kolumn liczbowych
        ('cat', OneHotEncoder(drop='first'), categorical_features)  # One-Hot-Encoding dla kolumn kategorycznych
    ]
)

# 1. Model 1: Regresja Ridge z cechami wielomianowymi
poly_features = PolynomialFeatures(degree=2, include_bias=False)  # Tworzenie cech wielomianowych stopnia 2
ridge_model = Pipeline(steps=[
    ('preprocessor', preprocessor),  # Przetwarzanie wstępne
    ('poly', poly_features),         # Dodanie cech wielomianowych
    ('ridge', Ridge(alpha=1.0))      # Regresja Ridge jako model
])

# Kroswalidacja dla modelu Ridge z powtórzonym K-Fold dla stabilnych wyników
cv = RepeatedKFold(n_splits=10, n_repeats=3, random_state=random_state)
ridge_scores = cross_val_score(ridge_model, X, y, cv=cv, scoring='r2')
print("Regresja Ridge z cechami wielomianowymi:")
print("Średni R² (kroswalidacja):", ridge_scores.mean())

# 2. Model 2: Regresor Gradient Boosting
gb_model = Pipeline(steps=[
    ('preprocessor', preprocessor),  # Przetwarzanie wstępne
    ('gb', GradientBoostingRegressor(n_estimators=100, learning_rate=0.1, random_state=random_state))
])

# Podział na zbiory treningowe i testowe
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=random_state)

# Trenowanie modelu Gradient Boosting
gb_model.fit(X_train, y_train)
y_pred_gb = gb_model.predict(X_test)

# Obliczanie metryk jakości dla modelu Gradient Boosting
gb_r2 = r2_score(y_test, y_pred_gb)
gb_mae = mean_absolute_error(y_test, y_pred_gb)
gb_mse = mean_squared_error(y_test, y_pred_gb)

print("\nGradient Boosting Regressor:")
print(f"R²: {gb_r2}")
print(f"MAE: {gb_mae}")
print(f"MSE: {gb_mse}")

# 3. Ważność cech (dla modelu Gradient Boosting)
# Pozwala zobaczyć, które cechy są najważniejsze dla modelu

# Wyciągnięcie ważności cech z modelu
gb_feature_importance = gb_model.named_steps['gb'].feature_importances_

# Pobranie nazw cech (numeryczne i zakodowane kategoryczne)
feature_names = (
    numeric_features +
    list(gb_model.named_steps['preprocessor'].named_transformers_['cat'].get_feature_names_out(categorical_features))
)

# Rysowanie wykresu ważności cech
plt.figure(figsize=(10, 8))
plt.barh(feature_names, gb_feature_importance, color='skyblue')
plt.xlabel('Ważność cech')
plt.title('Ważność cech dla Gradient Boosting Regressor')
plt.show()
