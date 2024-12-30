import time
from selenium import webdriver
from selenium.webdriver.common.by import By

from selenium.webdriver.chrome.service import Service

import requests
web=webdriver.Chrome()
web.get('http://5g.aioutx.com/pages/login-newadmin.html')
web.maximize_window()
time.sleep(3)
'''自动输入账号'''
web.find_element(by=By.ID,value='username').send_keys('liuhongyun')
time.sleep(1)
'''自动输入密码'''
web.find_element(by=By.ID,value='password').send_keys('Aa123456')
time.sleep(1)
'''自动点击按钮登录'''
web.find_element(by=By.CLASS_NAME,value='btn').click()
time.sleep(1)
'''查看客户管理'''
d=web.find_element(by=By.ID,value='_easyui_tree_1')
c=d.click()
time.sleep(40)
input("Press Enter to exit and close the browser...")
