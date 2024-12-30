from selenium import webdriver
import time
import json

driver = webdriver.Chrome()

def save_cookies(driver):
    """
    1. 打开登录页面；2. 人工登录；3. 自动保存Cookies到本地文件
    """
    # 最大化窗口
    driver.maximize_window()

    # 1. 打开登录的URL
    driver.get("https://atria.moyoung.com/login")

    # 2. Sleep 15秒钟，等待用户扫码
    time.sleep(15)

    # 3. 将登录后的cookies保存到本地文件
    with open("cookies.txt", "w", encoding="utf8") as f:
        f.write(json.dumps(driver.get_cookies(), indent=4, ensure_ascii=False))

driver.close()