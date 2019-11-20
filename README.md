# Talk SDK for iOS 使用指南

## 适用范围
本文档适用于游密实时语音引擎（Talk SDK）Xcode开发环境下接入。

## SDK目录概述
语音SDK中有两个子文件夹：include、lib,下面依次介绍下这两个子文件夹。

1. `include`：SDK的头文件。
  重点介绍inlude下的需要使用到的重要文件。
    * `YMVoiceService.h`封装了语音SDK的全部功能接口，集成方可通过[YMVoiceService getInstance]直接调用。
    * `VoiceEngineCallback.h`包含需要实现的语音SDK的回调接口协议。
    * `YouMeConstDefine.h`包含错误码定义等各类枚举类型定义。
2. `lib`：iOS库文件，包含libyoume_voice_engine.a文件和libYouMeCommon.a文件。

## 开发环境集成
 将SDK放置到xcode工程目录下（可视实际情况自行放置），如下图所示：
  
  ![](https://youme.im/doc/images/talk_ios_xcode_project.png)

### iOS系统Xcode开发环境配置
添加头文件和依赖库:
1. 打开XCode工程，找到工程目录，新建一个文件夹（可命名为SDKInclude），然后将SDK下的include文件夹里的头文件夹都加入进来(右键点击选择“Add Files to ...”)

  ![](https://youme.im/doc/images/talk_ios_xcode_addFiles.png)

2. 添加库文件路径：Build Settings -> Search Paths -> Library Search Paths，直接将SDK的ios文件夹拖到xcode需要填入的位置，然后路径会自动生成;
3. 添加依赖库：在Build Phases  -> Link Binary With Libraries下添加：`libc++.tbd`、`libsqlite3.0.tbd`、`libyoume_voice_engine.a`、`libYouMeCommon.a`、`libz.dylib`、`libz.1.2.5.tbd`、`libresolv.9.tbd`、`SystemConfiguration.framework`、`CoreTelephony.framework`、`AVFoundation.framework`、`AudioToolBox.framework`、`CFNetwork.framework`。
4. 为iOS10以上版本添加录音权限配置
iOS10系统使用录音权限，需要在target的`info.plist`中新加`NSMicrophoneUsageDescription`键，值为字符串(授权弹窗出现时提示给用户)。首次录音时会向用户申请权限。配置方式如下：
![iOS10录音权限配置](https://youme.im/doc/images/im_iOS_record_config.jpg)




##### 接口调用基本流程 
`实现回调(参考api手册里面的实现回调) -> 初始化（initSDK）->收到初始化成功回调通知 0(0表示sdk初始化成功)`->`加入语音单频道（joinChannelSingleMode ）->收到加入频道成功回调通知 2（2表示进入语音频道成功）`->`打开麦克风（setMicrophoneMute （false））->收到麦克风已打开回调通知 29(29表示自己麦克风被打开)->打开扬声器（setSpeakerMute （false））->收到扬声器已打开回调通知 31（31表示自己扬声器被打开）` ->`设置音量（setVolume （70）（该音量建议70））->(到了前面一步已经可以和当前进入同一频道的人进行实时通话了)`->`使用其他接口`
->`结束`



以上回调事件通知状态码更多详细请查看对应的状态码

### 备注：
[详细接口介绍可查看“Talk SDK for iOS API接口手册.md”文档](https://github.com/youmesdk/YoumeTalkSDK_iOS/blob/master/Talk%20SDK%20for%20iOS%20API接口手册.md)

实际Demo可以点击此处下载->[Talk Demo for iOS](https://github.com/youmesdk/YoumeTalkDemo_iOS)
