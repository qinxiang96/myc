import time
import json
from selenium import webdriver
#成功

def save_cookies(driver):
    cookies = driver.get_cookies()
    with open("cookies.txt", "w", encoding="utf8") as f:
        f.write(json.dumps(cookies))
    print("Cookies saved to cookies.txt")

def load_cookies(driver):
    try:
        with open("cookies.txt", encoding="utf8") as f:
            cookies = json.loads(f.read())
            for cookie in cookies:
                if 'name' in cookie and 'value' in cookie:
                    cookie.setdefault('path', '/')
                    cookie.setdefault('domain', driver.current_url.split("//")[1].split("/")[0])
                    driver.add_cookie(cookie)
                else:
                    print("Skipping invalid cookie:", cookie)
    except FileNotFoundError:
        print("cookies.txt not found. Please login and save cookies.")
    except Exception as e:
        print(f"Error loading cookies: {e}")

# WebDriver 初始化
driver = webdriver.Chrome()
driver.get("https://alphecca.moyoung.com/admin/project/117/job?_columns_=attribute%5B164%5D%2Cattribute%5B198%5D%2Cattribute%5B97%5D%2Ccreated_at%2Cid%2Cname%2Cstatus_id%2Cuser_id&creator_id%5B0%5D=482&status_id%5B0%5D=234&status_id%5B1%5D=255&status_id%5B2%5D=289&_sort%5Bcolumn%5D=created_at&_sort%5Btype%5D=asc")
time.sleep(5)

# 加载 cookies
load_cookies(driver)

# 登录完成后保存 cookies
save_cookies(driver)

# 保持浏览器窗口打开
input("Press Enter to exit...")
driver.quit()
