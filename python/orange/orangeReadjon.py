import json

import numpy as np
import pandas as pd
from Orange.data import Domain, StringVariable, Table
from Orange.data.pandas_compat import table_from_frame, table_to_frame

# JSON 파일 로드
with open('c:\BWLC217000037287.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

# 텍스트 데이터 추출
sentences = [item['sentence'] for entity in data['named_entity'] for item in entity['content']]

# pandas dataframe 으로 데이터 자장
data_df = pd.DataFrame(sentences, columns=['text'])

# Output
out_data = table_from_frame(data_df)
