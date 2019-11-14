# Talk SDK for IOS 电台主播模式

## 主要流程


###实现主播功能
####相关接口
(YouMeErrorCode_t) joinChannelSingleMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole_t)userRole checkRoomExist:(bool)checkRoomExist;  加入语音频道（单频道）

(void)setMicrophoneMute:(bool)mute;	设置麦克风状态

(void)setSpeakerMute:(bool)mute;		设置扬声器状态

(YouMeErrorCode_t)setHeadsetMonitorMicOn:(bool)micEnabled BgmOn:(bool)bgmEnabled;  设置监听

(YouMeErrorCode_t)setBackgroundMusicVolume:(unsigned int)bgVolume;	设置背景音乐播放音量

(YouMeErrorCode_t)playBackgroundMusic:(NSString *)path  repeat:(bool)repeat;		播放背景音乐

1.以主播身份进入频道
初始化（initSDK）->joinChannelSingleMode(参数三传主播身份YOUME_USER_HOST), 观众传的身份可以是听众 也可以是自由人（住进自由人进入频道 需要关闭麦克风）

2.上麦 调用setMicrophoneMute（false）  下麦调用
setMicrophoneMute（true）

3.设置监听 setHeadsetMonitorOn（true,true）参数1表示是否监听麦克风 true表示监听,false表示不监听 ,参数2表示是否监听背景音乐,true表示监听,false表示不监听

4.setBackgroundMusicVolume（70）调节背景音量大小

5.playBackgroundMusic(string pFilePath, bool bRepeat) 播放本地的mp3音乐。  参数一  本地音乐路径， 参数二 是否重复播放 true重复，false不重复




###实现送礼打赏

该功能需要IMSDK 并基于游密后台以及游密消息助手 （在消息助手显示，需要在后台的"主播管理"里面的"主播编辑"栏找到你需要匹配的主播频道 在"编辑"里面的"关联的IM频道ID" 填入你下面调用joinChatRoom频道   配置成功即可）

相关接口

Init  初始化

Login 登录

JoinChatRoom 进入频道

SendGift 发送礼物消息

OnRecvMessage 接收到礼物消息的消息回调



1.发送礼物的客户端先init(初始化)

2.通过JoinChatRoom进入主播频道（Talk）对应的IM频道（此对应需要在游密后台里面主播编辑配置,如果不使用我们的消息助手可以自己实现相关功能）当OnJoinRoom回调状态码返回0表示成功

3.调用sendGift接口发送礼物消息

	-(YIMErrorcodeOC) SendGift:(NSString*)anchorID channel:(NSString*)channel giftId:(int)giftId giftCount:(int)giftCount extraParam:(NSString*) extraParam requestID:(unsigned long long *)requestID ;
* **参数说明**

 `anchorID `:主播的userid，也就是后台配置的主播账号

 `channel `:主播所在的IM频道 

 `giftId `:后台"主播管理"里面的"礼物配置"里面对应的礼物标识，0表示只是留言

 `giftCount `:礼物物品数量

 `extraParam `:  扩展内容，参考ExtraGifParam类熟悉说明
 
 `requestID `:消息序列号

 
 **示例**
 




	



###白名单（进场通话模式）
	
	相关接口
	
	initSDK	初始化
	joinChannelSingleMode	进入单频道
	setWhiteUserList 		设置白名单
	
	
	1.调用initSDK初始化 当回调onEvent返回YOUME_EVENT_INIT_OK表示初始化成功
	
	2.调用joinChannelSingleMode  进入频道 单回调onEvent返回YOUME_EVENT_JOIN_OK表示进入频道成功
	
	3.调用SetWhiteUserList   当返回YOUME_EVENT_SET_WHITE_USER_LIST_OK事件 且状态码不是YOUME_ERROR_WHITE_SOMEUSER_ABNORMAL表示白名单设置成功
