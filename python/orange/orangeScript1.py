import pandas as pd
from Orange.data import Domain, Table
from Orange.data.pandas_compat import table_to_frame

# Orange 테이블을 pandas 데이터프레임으로 변환
data_df = table_to_frame(in_data, include_metas=True)

# categorie 열을 count 해서 피벗 테이블로 변환
data_df = data_df.groupby(['categorie']).size().reset_index(name='count')

# 피벗 테이블을 Orange 데이터 테이블로 변환
out_data = table_from_frame(data_df)
