import numpy as np
import pandas as pd
from Orange.data import Domain, Table
from Orange.data.pandas_compat import table_to_frame

# Orange 테이블을 pandas 데이터프레임으로 변환
data_df = table_to_frame(in_data, include_metas=True)

# data_df 의 내용을 모두 검색해서 점검중 이면 nan 으로 변경
data_df = data_df.replace('점검중', np.nan)

# data_df 의 날짜	시간	측정소명	수온	pH	용존산소	총질소	총인	총유기탄소	페놀	시안 으로 분리
# data_df_2 = data_df['시간'].astype(float)
# data_df_1 = data_df['측정소명'].astype(float)
# data_df_3 = data_df['날짜'].astype(float)
data_df_4 = data_df['수온'].astype(float)
data_df_5 = data_df['pH'].astype(float)
data_df_6 = data_df['용존산소'].astype(float)
data_df_7 = data_df['총질소'].astype(float)
data_df_8 = data_df['총인'].astype(float)
data_df_10 = data_df['페놀'].astype(float)
data_df_11 = data_df['시안'].astype(float)


# 다시 을 data_df 에 합치기
data_df['수온'] = data_df_4
data_df['pH'] = data_df_5
data_df['용존산소'] = data_df_6
data_df['총질소'] = data_df_7
data_df['총인'] = data_df_8
data_df['페놀'] = data_df_10
data_df['시안'] = data_df_11


# 피벗 테이블을 Orange 데이터 테이블로 변환
out_data = table_from_frame(data_df)
