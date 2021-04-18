# BasicInfoNMaintain
qtpm基础信息文件维护模块。
本模块更加亲密于json格式的解析，基类方法对json格式的解读非常友好，但是对其他格式可能并不是非常友好。
使用方法很简单，只要调用两个class就好。
对于读取json格式，只要使用 jsonread类
对于读写json，只要使用jsonwrite类。
本项目的特点在于可以追踪json的key

对形如
 "Version": {
        "demo2": {
            "22": "2222"
        },
        "demo4": {
            "22": "4442224"
        }
    },
    
要想获取demo4下面的22的值
只需输入 Version:demo4:22即可。非常脑残！
