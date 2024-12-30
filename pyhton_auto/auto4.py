#encoding=utf-8 
import urllib.request
import urllib.error 
import urllib 
import http.cookiejar
import urllib.parse
#不行
def renrenBrower(url,user,password): 
  #登陆页面，可以通过抓包工具分析获得，如fiddler，wireshark 
  login_page = "https://atria.moyoung.com/login" 
  try: 
    #获得一个cookieJar实例 
    cj = http.cookiejar.CookieJar() 
    #cookieJar作为参数，获得一个opener的实例 
    opener=urllib.request.build_opener(urllib.request.HTTPCookieProcessor(cj)) 
    #伪装成一个正常的浏览器，避免有些web服务器拒绝访问。 
    opener.addheaders = [('User-agent','Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)')] 
    #生成Post数据，含有登陆用户名密码。 
    data = urllib.parse.urlencode({"email":user,"password":password}) 
    #以post的方法访问登陆页面，访问之后cookieJar会自定保存cookie 
    opener.open(login_page,data) 
    #以带cookie的方式访问页面 
    op=opener.open(url) 
    #读取页面源码 
    data= op.read() 
    return data 
  except (ValueError, TypeError) as e: 
    print("出错啦") 
#访问某用户的个人主页，其实这已经实现了人人网的签到功能。 
print (renrenBrower("https://alphecca.moyoung.com/admin/resource/project","Rebecca","fZ7oA5qD1") )