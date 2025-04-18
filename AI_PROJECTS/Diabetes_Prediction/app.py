import streamlit as st
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# ML and evaluation libraries
from sklearn.ensemble import RandomForestClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from xgboost import XGBClassifier
from sklearn.model_selection import train_test_split, cross_val_score, StratifiedKFold
from sklearn.metrics import (accuracy_score, precision_score, recall_score, f1_score,
                             confusion_matrix, roc_auc_score, roc_curve, auc)
from imblearn.over_sampling import SMOTE

#-------------------------------------------
# Function definitions
#-------------------------------------------

@st.cache_data
def load_dataset():
    # Load the Pima Indians Diabetes dataset
    url = "https://raw.githubusercontent.com/jbrownlee/Datasets/master/pima-indians-diabetes.data.csv"
    columns = ['Pregnancies', 'Glucose', 'BloodPressure', 'SkinThickness', 'Insulin', 
               'BMI', 'DiabetesPedigreeFunction', 'Age', 'Outcome']
    data = pd.read_csv(url, header=None, names=columns)
    
    # Replace zeroes with the median for some columns
    for col in ['Glucose', 'BloodPressure', 'SkinThickness', 'Insulin', 'BMI']:
        data[col] = data[col].replace(0, data[col].median())
    return data

@st.cache_data
def prepare_data(data, balance_data=False):
    X = data.drop('Outcome', axis=1)
    y = data['Outcome']
    
    # Optionally balance the dataset using SMOTE
    if balance_data:
        smote = SMOTE(random_state=42)
        X, y = smote.fit_resample(X, y)
    
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    return X_train, X_test, y_train, y_test

def calculate_metrics(y_true, y_pred):
    tn, fp, fn, tp = confusion_matrix(y_true, y_pred).ravel()
    specificity = tn / (tn + fp)
    sensitivity = recall_score(y_true, y_pred)
    return {
        'Accuracy': accuracy_score(y_true, y_pred),
        'Precision': precision_score(y_true, y_pred),
        'Sensitivity (Recall)': sensitivity,
        'Specificity': specificity,
        'F1-Measure': f1_score(y_true, y_pred)
    }

@st.cache_data
def train_models(X_train, X_test, y_train, y_test):
    # Define models
    models = {
        "Random Forest": RandomForestClassifier(random_state=42),
        "Decision Tree": DecisionTreeClassifier(random_state=42),
        "SVM": SVC(kernel='rbf', probability=True, random_state=42),
        "XGBoost": XGBClassifier(use_label_encoder=False, eval_metric='logloss', random_state=42)
    }
    
    model_metrics = {}
    roc_data = {}
    confusion_mats = {}

    for name, model in models.items():
        model.fit(X_train, y_train)
        y_pred = model.predict(X_test)
        metrics = calculate_metrics(y_test, y_pred)
        model_metrics[name] = metrics

        # ROC and AUC
        y_pred_prob = model.predict_proba(X_test)[:, 1]
        fpr, tpr, _ = roc_curve(y_test, y_pred_prob)
        model_roc_auc = auc(fpr, tpr)
        roc_data[name] = (fpr, tpr, model_roc_auc)
        
        # Confusion matrix
        confusion_mats[name] = confusion_matrix(y_test, y_pred)
    
    return models, model_metrics, roc_data, confusion_mats

def perform_kfold(X, y, models, k=5):
    kf = StratifiedKFold(n_splits=k, shuffle=True, random_state=42)
    kfold_results = {}
    for name, model in models.items():
        auc_scores = cross_val_score(model, X, y, cv=kf, scoring='roc_auc')
        kfold_results[name] = {
            'Mean AUC-ROC': auc_scores.mean(),
            'Std AUC-ROC': auc_scores.std()
        }
    return kfold_results

#-------------------------------------------
# Streamlit UI Layout
#-------------------------------------------

# Title and Project Overview
st.title("Diabetes Prediction Model Using Machine Learning")
st.markdown("""
This interactive dashboard presents the implementation of a Diabetes Prediction Model 
using several machine learning classification algorithms. It includes data preprocessing, 
model training on both balanced and unbalanced datasets, and displays various evaluation metrics.
""")

# Sidebar for navigation
section = st.sidebar.selectbox("Navigation", 
                               ["Project Overview", "Dataset Exploration", "Model Metrics", "Visualizations", "Cross-Validation"])

# Load dataset
data = load_dataset()

if section == "Project Overview":
    st.header("Project Overview")
    st.markdown("""
    **Subject Code:** IT – 306  
    **Project Title:** IEEE Transaction Paper Implementation on Diabetes Prediction Model  
    **Submitted By:** Nikhil Sharma & Parth Goel  
    **Submitted To:** Ms. Bhawna Kashyap  

    The goal of the project is to build a machine learning model that can predict diabetes using the Pima Indians Diabetes dataset.
    The app demonstrates:
    - Data preprocessing (imputation, balancing using SMOTE)
    - Model training using Random Forest, Decision Tree, SVM, and XGBoost.
    - Evaluation of models using metrics like Accuracy, Precision, Sensitivity, Specificity, F1-Measure, and ROC-AUC.
    - Visualization of correlations, confusion matrices, and ROC curves.
    """)
    
elif section == "Dataset Exploration":
    st.header("Dataset Exploration")
    st.subheader("Data Overview")
    st.write(data.head())
    st.write("**Dataset Information:**")
    buffer = st.empty()
    # Capture info output as text
    import io
    info_buf = io.StringIO()
    data.info(buf=info_buf)
    s = info_buf.getvalue()
    st.text(s)
    st.write("**Statistical Summary:**")
    st.write(data.describe())
    
    st.subheader("Correlation Heatmap")
    plt.figure(figsize=(10, 8))
    corr_matrix = data.corr()
    sns.heatmap(corr_matrix, annot=True, cmap='coolwarm', fmt=".2f")
    st.pyplot(plt.gcf())
    plt.clf()

elif section == "Model Metrics":
    st.header("Model Training and Metrics")
    balance_option = st.radio("Choose Dataset Type:", ("Unbalanced", "Balanced"))
    
    if balance_option == "Unbalanced":
        # Prepare unbalanced data
        X_train, X_test, y_train, y_test = prepare_data(data, balance_data=False)
    else:
        # Prepare balanced data using SMOTE
        X_train, X_test, y_train, y_test = prepare_data(data, balance_data=True)
    
    models, model_metrics, roc_data, confusion_mats = train_models(X_train, X_test, y_train, y_test)
    
    st.subheader("Performance Metrics")
    metrics_df = pd.DataFrame(model_metrics).T
    st.dataframe(metrics_df.style.highlight_max(axis=0))
    
    st.markdown("The table above summarizes the performance of all models on the selected dataset type.")

elif section == "Visualizations":
    st.header("Visualizations")
    
    balance_option = st.radio("Select Dataset for Visualization:", ("Unbalanced", "Balanced"), key="viz")
    
    if balance_option == "Unbalanced":
        X_train, X_test, y_train, y_test = prepare_data(data, balance_data=False)
    else:
        X_train, X_test, y_train, y_test = prepare_data(data, balance_data=True)
    
    models, model_metrics, roc_data, confusion_mats = train_models(X_train, X_test, y_train, y_test)
    
    st.subheader("ROC-AUC Curve")
    plt.figure(figsize=(10, 8))
    for name, (fpr, tpr, roc_auc) in roc_data.items():
        plt.plot(fpr, tpr, label=f'{name} (AUC = {roc_auc:.2f})')
    plt.plot([0, 1], [0, 1], 'k--')  # random classifier line
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('ROC-AUC Curves')
    plt.legend(loc="lower right")
    st.pyplot(plt.gcf())
    plt.clf()
    
    st.subheader("Confusion Matrices")
    for name, cm in confusion_mats.items():
        st.write(f"**{name}**")
        fig, ax = plt.subplots(figsize=(4, 4))
        sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', ax=ax)
        ax.set_xlabel("Predicted")
        ax.set_ylabel("Actual")
        st.pyplot(fig)
        plt.clf()

elif section == "Cross-Validation":
    st.header("K-Fold Cross-Validation")
    balance_option = st.radio("Select Dataset for Cross-Validation:", ("Unbalanced", "Balanced"), key="cv")
    
    if balance_option == "Unbalanced":
        X = data.drop('Outcome', axis=1)
        y = data['Outcome']
    else:
        smote = SMOTE(random_state=42)
        X, y = smote.fit_resample(data.drop('Outcome', axis=1), data['Outcome'])
    
    # Define the same models as before
    models_cv = {
        "Random Forest": RandomForestClassifier(random_state=42),
        "Decision Tree": DecisionTreeClassifier(random_state=42),
        "SVM": SVC(kernel='rbf', probability=True, random_state=42),
        "XGBoost": XGBClassifier(use_label_encoder=False, eval_metric='logloss', random_state=42)
    }
    
    kfold_results = perform_kfold(X, y, models_cv, k=5)
    cv_df = pd.DataFrame(kfold_results).T
    st.dataframe(cv_df.style.highlight_max(axis=0))
    st.markdown("The table shows the mean ROC-AUC and its standard deviation from 5-fold cross-validation for each model.")
