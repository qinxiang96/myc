import json
from selenium import webdriver
import pandas as pd
from bs4 import BeautifulSoup


driver = webdriver.Chrome()

def load_cookies(driver):
    """
    1. 访问一下登录的URL；2. 加载本地的Cookies；3. 刷新一下浏览器；
    """
    # 最大化窗口
    driver.maximize_window()
    # 访问一下登录的URL
    driver.get("https://atria.moyoung.com/login")

    # 读取本地的Cookies文件，加载到driver
    with open("cookies.txt", encoding="utf8") as f:
        cookies = json.loads(f.read())
        for cookie in cookies:
            driver.add_cookie(cookie)
    # 刷新一下浏览器
    driver.refresh()

load_cookies(driver)

# 直接访问需要登录的页面
driver.get("https://alphecca.moyoung.com/admin/project/117/job?_columns_=attribute%5B164%5D%2Cattribute%5B198%5D%2Cattribute%5B97%5D%2Ccreated_at%2Cid%2Cname%2Cstatus_id%2Cuser_id&creator_id%5B0%5D=482&status_id%5B0%5D=234&status_id%5B1%5D=255&status_id%5B2%5D=289&_sort%5Bcolumn%5D=created_at&_sort%5Btype%5D=asc")

# 获取页面 HTML
html = driver.page_source
print(html)
# # 使用 BeautifulSoup 解析 HTML
# soup = BeautifulSoup(html, 'html.parser')

# # 找到 class="tables-container" 的标签
# container = soup.find('table', class_='.custom-data-table.table.custom-data-table.data-table.table-bordered.complex-headers')

# # 提取 class="tables-container" 内的所有表格
# if container:
#     tables = container.find_all('table')  # 找到所有表格
#     all_data = []
#     for i, table in enumerate(tables):
#         print(f"Table {i}:")
#         # 将表格转换为 Pandas DataFrame
#         df = pd.read_html(str(table))[0]
#         all_data.append(df)
#         print(df)
# else:
#     print("No tables found in 'tables-container'.")

driver.close()