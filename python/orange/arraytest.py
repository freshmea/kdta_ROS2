
# array subscripting
# f-string
abc = 1
print(f'{abc}')
# f-string 중첩
print(f'{f"{abc}"}')
# f-string 여러줄 표현과 주석 포함
print(f'''
{f"{abc}"}
# 이것도 됨?
ㅁㄴㅇㄹ''')
songs = ['Take me back to Eden', 'Alkaline', 'Ascensionism']
print(f"This is the playlist: {', '.join([
    'Take me back to Eden',  # 첫 번째 노래
    'Alkaline',              # 두 번째 노래
    'Ascensionism'           # 세 번째 노래
])}")