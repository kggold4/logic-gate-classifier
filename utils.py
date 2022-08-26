import numpy as np
import pandas as pd

def generate_data(n: int = 10, m: int = 4):
    data = {}
    for feature in range(m):
        data[f"data {feature + 1}"] = [np.random.randint(0, 10) for _ in range(n)]
    data["result"] = [np.random.randint(0, 10) for _ in range(n)]
    return pd.DataFrame(data)