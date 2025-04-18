import streamlit as st
import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
import numpy as np

# Sample Dataset: A DataFrame with course details.
data = {
    'CourseID': [1, 2, 3, 4, 5],
    'CourseName': [
        "Python for Beginners", 
        "Advanced Machine Learning", 
        "Data Science Fundamentals", 
        "Web Development Bootcamp", 
        "Deep Learning with TensorFlow"
    ],
    'Description': [
        "Learn basics of Python programming", 
        "Learn advanced topics in machine learning and algorithms", 
        "Introduction to data science techniques and tools", 
        "Learn HTML, CSS, JavaScript and backend development", 
        "Hands-on deep learning course using TensorFlow framework"
    ],
    'Tags': [
        "python, basics, programming", 
        "machine learning, advanced, algorithms", 
        "data science, fundamentals, analytics", 
        "web development, full stack, design", 
        "deep learning, tensorflow, neural networks"
    ]
}

# Create DataFrame from sample data.
df = pd.DataFrame(data)

st.title("Course Recommendation System")
st.write("Select a course below to get similar course recommendations.")

# Combine Description and Tags to form a combined text feature.
df['Combined'] = df['Description'] + " " + df['Tags']

# Vectorize the combined text using TF-IDF.
vectorizer = TfidfVectorizer(stop_words='english')
tfidf_matrix = vectorizer.fit_transform(df['Combined'])

# Compute the cosine similarity matrix.
cosine_sim = cosine_similarity(tfidf_matrix, tfidf_matrix)

# Function to get course recommendations based on cosine similarity.
def get_recommendations(course_name, cosine_sim=cosine_sim):
    # Get the index of the course that matches the course name.
    idx = df.index[df['CourseName'] == course_name].tolist()[0]
    
    # Get pairwise cosine similarity scores for that course.
    sim_scores = list(enumerate(cosine_sim[idx]))
    
    # Sort the courses based on the similarity scores.
    sim_scores = sorted(sim_scores, key=lambda x: x[1], reverse=True)
    
    # Exclude the first one, which is the course itself.
    sim_scores = sim_scores[1:4]  # top 3 recommendations
    
    # Get the course indices.
    course_indices = [i[0] for i in sim_scores]
    
    return df.iloc[course_indices][['CourseID', 'CourseName', 'Description']]

# UI: Course selection
course_names = df['CourseName'].tolist()
selected_course = st.selectbox("Select a course:", course_names)

if st.button("Get Recommendations"):
    recommendations = get_recommendations(selected_course)
    st.write("### Recommended Courses:")
    st.table(recommendations)

# Additional explanation in sidebar
st.sidebar.header("Project Details")
st.sidebar.markdown("""
**Tech Stack:**

- **Programming Language:** Python  
- **Framework:** Streamlit (for UI)  
- **Libraries:**  
  - `pandas` for data handling  
  - `scikit-learn` for vectorization and similarity computation  
  - `numpy` for numerical operations  

**Algorithm Used:**
- **TF-IDF Vectorization:** To convert course descriptions and tags into numeric features.  
- **Cosine Similarity:** For calculating similarity between courses.

**How to Run:**
1. Install required libraries:
2. Save this code in a file named `app.py`.
3. Run the app with:
streamlit run app.py
4. Open the provided URL in your browser and interact with the UI.
""")