//
//  YMVoiceService.h
//  YmTalkTestRef
//
//  Created by pinky on 2017/5/27.
//  Copyright © 2017年 Youme. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VoiceEngineCallback.h"



@interface YMVoiceService : NSObject
@property (nonatomic) id<VoiceEngineCallback> delegate;

//公共接口
+ (YMVoiceService *)getInstance;
+ (void)destroy;

- (void)setTestServer:(bool) isTest;

/**
 *  功能描述:初始化引擎
 *
 *  @param delegate:回调地址
 *  @param appkey:在申请SDK注册时得到的App Key，也可凭账号密码到http://gmx.dev.net/createApp.html查询
 *  @param appSecret:在申请SDK注册时得到的App Secret，也可凭账号密码到http://gmx.dev.net/createApp.html查询
 *  @param region:可选的服务器区域
 *  @param serverRegionName:
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t)initSDK:(id<VoiceEngineCallback>)delegate  appkey:(NSString*)appKey  appSecret:(NSString*)appSecret
        regionId:(YOUME_RTC_SERVER_REGION_t)regionId
           serverRegionName:(NSString*) serverRegionName;

/**
 *  功能描述:设置身份验证的token
 *  @param token: 身份验证用token，设置空字符串，清空token值。
 *  @return 无
 */
- (void)setToken:(NSString*) token;

/**
 *  功能描述:反初始化引擎
 *
 *  @return 错误码
 */
- (YouMeErrorCode_t)unInit;

/**
 *  功能描述:设置服务器区域
 *  @param region: 可选的服务器区域
 *  @return 无
 */
-(void)setServerRegion:(YOUME_RTC_SERVER_REGION_t)serverRegionId regionName:(NSString*)regionName bAppend:(bool)bAppend;

/**
 *  功能描述:切换语音输出设备
 *  默认输出到扬声器，在加入房间成功后设置（iOS受系统限制，如果已释放麦克风则无法切换到听筒）
 *
 *  @param bOutputToSpeaker:true——使用扬声器，false——使用听筒
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t)setOutputToSpeaker:(bool)bOutputToSpeaker;

/**
 *  功能描述:设置扬声器静音
 *
 *  @param mute:true——静音，false——取消静音
 *  @return 无
 */
-(void)setSpeakerMute:(bool)mute;

/**
 *  功能描述:获取扬声器静音状态
 *
 *  @return true——静音，false——没有静音
 */
-(bool)getSpeakerMute;

/**
 *  功能描述:获取麦克风静音状态
 *
 *  @return true——静音，false——没有静音
 */
-(bool)getMicrophoneMute;

/**
 *  功能描述:设置麦克风静音
 *
 *  @param mute:true——静音，false——取消静音
 *  @return 无
 */
-(void)setMicrophoneMute:(bool)mute;

/**
 *  功能描述:设置是否通知其他人自己的开关麦克风和扬声器的状态
 *
 *  @param bAutoSend:true——通知，false——不通知
 *  @return 无
 */
-(void)setAutoSendStatus:(bool)bAutoSend;

/**
 *  功能描述:获取音量大小,此音量值为程序内部的音量，与系统音量相乘得到程序使用的实际音量
 *
 *  @return 音量值[0,100]
 */
- (unsigned int)getVolume;
/**
 *  功能描述:增加音量，音量数值加1
 *
 *  @return 无
 */
- (void)setVolume:(unsigned int)uiVolume;

/**
 *  功能描述:获取麦克风音量增益大小,此音量值为程序内部的麦克风音量增益值，与系统音量相乘得到程序使用的实际音量
 *
 *  @return 音量值[0,1000] >100增益，<100减益
 */
- (unsigned int)getMicVolume;
/**
 *  功能描述:设置麦克风音量增益[0-1000]，>100增益，<100减益
 *
 *  @return 无
 */
- (void)setMicVolume:(unsigned int)uiVolume;

/**
 *  功能描述:启用/禁用移动网络
 *
 *  @param bEnabled:true-可以启用，false-禁用，默认禁用
 *
 *  @return 无
 */
- (void)setUseMobileNetworkEnabled:(bool)bEnabled;

/**
 *  功能描述:是否可使用移动网络
 *
 *  @return true-可以使用，false-禁用
 */
- (bool) getUseMobileNetworkEnabled;

//多人语音接口
/**
 *  功能描述:加入语音频道（单频道模式，每个时刻只能在一个语音频道里面）
 *
 *  @param strUserID: 用户ID，要保证全局唯一
 *  @param strChannelID: 频道ID，要保证全局唯一
 *  @param userRole: 用户角色，用于决定讲话/播放背景音乐等权限
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t) joinChannelSingleMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole_t)userRole;

/**
 *  功能描述:加入语音频道（单频道模式，每个时刻只能在一个语音频道里面）
 *
 *  @param strUserID: 用户ID，要保证全局唯一
 *  @param strChannelID: 频道ID，要保证全局唯一
 *  @param userRole: 用户角色，用于决定讲话/播放背景音乐等权限
 *  @param bCheckRoomExist:是否检查频道存在时才加入，默认为false: true 当频道存在时加入、不存在时返回错误（多用于观众角色），false 无论频道是否存在都加入频道
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t) joinChannelSingleMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole_t)userRole checkRoomExist:(bool)checkRoomExist;

/**
 *  功能描述：加入语音频道（多频道模式，可以同时在多个语音频道里面）
 *
 *  @param strUserID: 用户ID，要保证全局唯一
 *  @param strChannelID: 频道ID，要保证全局唯一
 *  @param userRole: 用户角色，用于决定讲话/播放背景音乐等权限
 *  @param bCheckRoomExist:是否检查频道存在时才加入，默认为false: true 当频道存在时加入、不存在时返回错误（多用于观众角色），false 无论频道是否存在都加入频道
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t) joinChannelMultiMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole_t)userRole checkRoomExist:(bool)checkRoomExist;

/**
 *  功能描述：加入语音频道（多频道模式，可以同时在多个语音频道里面）
 *
 *  @param strUserID: 用户ID，要保证全局唯一
 *  @param strChannelID: 频道ID，要保证全局唯一
 *  @param userRole: 用户角色，用于决定讲话/播放背景音乐等权限
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t) joinChannelMultiMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole_t)userRole;

/**
 *  功能描述：对指定频道说话
 *
 *  @param strChannelID: 频道ID，要保证全局唯一
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t) speakToChannel:(NSString *)strChannelID;

//退出音频会议
/**
 *  功能描述:退出多频道模式下的某个语音频道
 *
 *  @param strChannelID:频道ID，要保证全局唯一
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t)leaveChannelMultiMode:(NSString *)strChannelID;

/**
 *  功能描述:退出所有语音频道
 *
 *  @return 错误码
 */
- (YouMeErrorCode_t)leaveChannelAll;



/**
 *  功能描述:获取SDK 版本号
 *
 *
 *  @return 整形数字版本号
 */
- (int)getSDKVersion;

/**
 *  功能描述:控制其他人的麦克风开关
 *
 *  @param strUserID:用户ID，要保证全局唯一
 *  @param mute: true 静音对方的麦克风，false 取消静音对方麦克风
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
-(void) setOtherMicMute:(NSString *)strUserID  mute:(bool) mute;

/**
 *  功能描述:控制其他人的扬声器开关
 *
 *  @param strUserID:用户ID，要保证全局唯一
 *  @param mute: true 静音对方的扬声器，false 取消静音对方扬声器
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
-(void) setOtherSpeakerMute: (NSString *)strUserID  mute:(bool) mute;

/**
 *  功能描述:选择消除其他人的语音
 *
 *  @param strUserID:用户ID，要保证全局唯一
 *  @param isOn: false屏蔽对方语音，true取消屏蔽
 *
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
-(void) setListenOtherVoice: (NSString *)strUserID  isOn:(bool) isOn;

/**
 *  功能描述: 播放背景音乐，并允许选择混合到扬声器输出麦克风输入
 *  @param pFilePath 音乐文件的路径
 *  @param repeat 是否重复播放
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)playBackgroundMusic:(NSString *)path  repeat:(bool)repeat;

/**
 *  功能描述:获取背景音乐总时长
 *
 *  @return 音频时长，单位ms
*/
- (long long)getBgmDuration;

/**
 *  功能描述:获取背景音乐播放进度
 *
 *  @return 进度范围(0,音频时长]，单位ms
*/
- (long long)getBgmProgress;

/**
 *  功能描述:控制背景音乐播放进度
 *  bgmProgress: (0, 音频时长]，单位ms
 *  @return 无
*/
- (void)setBgmProgress:(long long)bgmProgress;

/**
 *  功能描述: 如果当前正在播放背景音乐的话，暂停播放
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)pauseBackgroundMusic;

/**
 *  功能描述: 如果当前背景音乐处于暂停状态的话，恢复播放
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)resumeBackgroundMusic;

/**
 *  功能描述: 如果当前正在播放背景音乐的话，停止播放
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)stopBackgroundMusic;

/**
 *  功能描述: 设置背景音乐播放的音量
 *  @param vol 背景音乐的音量，范围 0-100
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)setBackgroundMusicVolume:(unsigned int)bgVolume;

/**
 *  功能描述: 获取背景音乐播放的音量
 *  @return vol 背景音乐的音量，范围 0-100
 */
- (int)getBackgroundMusicVolume;

/**
 *  功能描述: 设置监听时mic的音量
 *  @param vol 监听时mic的音量，范围 0-100
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)setMicbypassVolume:(unsigned int)vol;

/**
 *  功能描述: 获取监听时mic的音量
 *  @return vol 监听时mic的音量，范围 0-100
 */
- (int)getMicbypassVolume;

/**
 *  功能描述:播放音效
 *  @param path 音效文件的路径
 *  @param repeatCount 重复播放次数，-1表示无限循环，0 播放1次， 1 播放两次
 *  @param effectId 返回音效的标识，为nil标识不关心
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)playEffect:(NSString *)path  repeatCount:(int)repeatCount effectId:(int*)effectId;


/**
 *  功能描述:停止音效
 *  @param effectId 要停止的音效的id
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)stopEffect:(int)effectId;


/**
 *  功能描述:停止音效
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)stopAllEffects;

/**
 *  功能描述:暂停音效
 *  @param effectId 要暂停的音效Id
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) pauseEffect:(int) effectId;

/**
 *  功能描述:恢复音效
 *  @param effectId 要暂停的音效Id
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) resumeEffect:(int) effectId;

/**
 *  功能描述:暂停所有音效
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) pauseAllEffects;

/**
 *  功能描述:恢复所有音效
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) resumeAllEffects;

/**
 *  功能描述: 设置音效播放的音量
 *  @param vol 音效的音量，范围 0-100
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)setEffectVolume:(unsigned int)effectVolume;

/**
 *  功能描述: 获取音效播放的音量
 *  @return vol 音效的音量，范围 0-100
 */
- (int)getEffectVolume;

/**
 *  功能描述: 设置是否监听自己的麦克风声音（打开背景音乐监听）
 *  @param micEnabled 是否监听麦克风 true 监听，false 不监听
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)setHeadsetMonitorMicOn:(bool)micEnabled;

/**
 *  功能描述: 设置是否监听自己的声音或背景音乐
 *  @param micEnabled 是否监听麦克风 true 监听，false 不监听
 *  @param bgmEnabled 是否监听背景音乐 true 监听，false 不监听
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)setHeadsetMonitorMicOn:(bool)micEnabled BgmOn:(bool)bgmEnabled;

/**
 *  功能描述: 设置是否开启主播混响模式
 *  @param enabled, true 开启，false 关闭
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)setReverbEnabled:(bool)enabled;

/**
 *  功能描述: 设置音频混响效果类型
 *  @param effectType, [1,6]
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)setAudioEffectType:(unsigned int)effectType;

/**
 *  功能描述: 设置是否开启语音检测回调
 *  @param enabled, true 开启，false 关闭
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)setVadCallbackEnabled:(bool)enabled;

/**
 *  功能描述: 设置是否开启讲话音量回调, 并设置相应的参数
 *  @param maxLevel, 音量最大时对应的级别，最大可设100。根据实际需要设置小于100的值可以减少回调的次数。
 *                   比如你只在UI上呈现10级的音量变化，那就设10就可以了。
 *                   设 0 表示关闭回调。
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setMicLevelCallback:(int) maxLevel;

/**
 *  功能描述: 设置是否开启远端说话人音量回调, 并设置相应的参数
 *  @param maxLevel, 音量最大时对应的级别，最大可设100。
 *                   比如你只在UI上呈现10级的音量变化，那就设10就可以了。
 *                   设 0 表示关闭回调。
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setFarendVoiceLevelCallback:(int) maxLevel;


/**
 *  功能描述: 设置当麦克风静音时，是否释放麦克风设备，在初始化之后、加入房间之前调用
 *  @param enabled,
 *      true 当麦克风静音时，释放麦克风设备，此时允许第三方模块使用麦克风设备录音。在Android上，语音通过媒体音轨，而不是通话音轨输出。
 *      false 不管麦克风是否静音，麦克风设备都会被占用。
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setReleaseMicWhenMute:(bool) enabled;

/**
 *  功能描述: 设置插入耳机时，是否自动禁用手机系统硬件信号前处理
 *          系统提供的前处理效果包括回声消除、自动增益等，有助于抑制背景音乐等回声噪音，减少系统资源消耗，对Windows系统无效
 *          由于插入耳机可从物理上阻断回声产生，故可设置禁用该效果以保留背景音乐的原生音质效果
 *          默认为false，在初始化之后、加入房间之前调用
 *  @param enabled,
 *      true 当插入耳机时，自动禁用系统硬件信号前处理，拔出时还原
 *      false 插拔耳机不做处理
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setExitCommModeWhenHeadsetPlugin:(bool) enabled;

/**
 *  功能描述: 设置频道音频模式
 *
 *  @param audioMode,
 *      CHANNEL_AUDIO_MODE_CALL 通话模式，激活系统的通话模式，优化对人声的通话体验
 *      CHANNEL_AUDIO_MODE_HQ_MUSIC 高音质音乐模式，着重优化音乐播放的效果，可能会产生额外费用
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setChannelAudioMode:(ChannelAudioMode_t) audioMode;

/**
 *  功能描述:设置是否为外置声卡模式，外置声卡模式关闭软件音频信号前处理（包含回声消除、噪声消除等），
 *  声卡内录模式播放音乐的场景中，戴耳机的情况下可以强制关闭，提高音乐质量
 *
 *  @param isExternalSoundCard,
 *      true 外置声卡模式，强制禁用软件音频信号前处理
 *      false 取消强制禁用软件音频信号前处理
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setExternalSoundCardMode:(bool) isExternalSoundCard;

/**
 *  功能描述: 设置是否强制关闭软件AEC 处理,声卡内录模式播放音乐的话，戴耳机的情况下可以强制关闭，提高音乐质量
 *
 *  @param disable,
 *      true 强制禁用软件AEC
 *      false 取消强制禁用软件AEC
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setForceDisableAEC:(bool) disable;

/**
 *  功能描述: 设置是否强制关闭软件 AGC 处理,声卡内录模式播放音乐的话，戴耳机的情况下可以强制关闭，提高音乐质量
 *
 *  @param disable,
 *      true 强制禁用软件AGC
 *      false 取消强制禁用软件AEC
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setForceDisableAGC:(bool) disable;

/**
 *  功能描述: 暂停通话，释放麦克风等设备资源
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)pauseChannel;

/**
 *  功能描述: 恢复通话
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)resumeChannel;

/**
 *  功能描述: 设置当前录音的时间戳
 *  @return  None
 */
- (void) setRecordingTimeMs:(unsigned int)timeMs;

/**
 *  功能描述: 设置当前播放的时间戳
 *  @return  None
 */
- (void) setPlayingTimeMs:(unsigned int)timeMs;

/**
 *  功能描述: 获取变声音调（增值服务，需要后台配置开启）
 *  @return 变声音调，范围为-12~12，0为原声，值越高音调越高
 */
- (float) getSoundtouchPitchSemiTones;

/**
 *  功能描述: 设置变声音调（增值服务，需要后台配置开启）
 *  @param fPitchSemiTones: 变声音调，范围为-12~12，0为原声，值越高音调越高
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (int) setSoundtouchPitchSemiTones:(float) fPitchSemiTones;

/**
 *  功能描述:Rest API , 向服务器请求额外数据
 *  @param requestID: 回传id,回调的时候传回，标识消息
 *  @param strCommand: 请求的命令字符串
 *  @param strQueryBody: 请求需要的数据,json格式，内容参考restAPI
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t)requestRestApi:(NSString*) strCommand strQueryBody:(NSString*) strQueryBody requestID:(int*)requestID;

/**
 *  功能描述:切换身份(仅支持单频道模式，进入房间以后设置)
 *  @param eUserRole: 用户身份
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t)setUserRole:(YouMeUserRole_t) eUserRole;

/**
 *  功能描述:获取身份(仅支持单频道模式)
 *  @return 身份定义，详见YouMeConstDefine.h定义
 */
- (YouMeUserRole_t) getUserRol;

/**
 *  功能描述:查询频道的用户列表
 *  @param channelID:要查询的频道ID
 *  @param maxCount:想要获取的最大数量，-1表示获取全部
 *  @param notifyMemChagne: 其他用户进出房间时，是否要收到通知
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t) getChannelUserList:(NSString*) channelID maxCount:(int)maxCount notifyMemChange:(bool)notifyMemChange ;


/**
 *  功能描述: 设置PCM数据回调
 *  @param  pcmCallback:实现pcm回调处理的对象
 *  @param  flag:有3中pcm回调，分别为远端pcm,本地录音pcm及远端和录音的混合pcm。flag用于标记打开哪几种回调，形如PcmCallbackFlag_Remote| PcmCallbackFlag_Record|PcmCallbackFlag_Mix。
 *  @param  bOutputToSpeaker 是否扬声器静音:true 不静音;false 静音
 *  @param  nOutputSampleRate pcm callback重采样的采样率
 *  @param  nOutputChannel pcm callback重采样的通道数
 *  @return 错误码，详见YouMeConstDefine.h定义
 */
- (YouMeErrorCode_t) setPcmCallbackEnable:(int) flag outputToSpeaker:(bool)bOutputToSpeaker nOutputSampleRate:(int)nOutputSampleRate nOutputChannel:(int)nOutputChannel;


//---------------------抢麦接口---------------------//
/**
* 功能描述:    抢麦相关设置（抢麦活动发起前调用此接口进行设置）
* @param pChannelID: 抢麦活动的频道id
* @param mode: 抢麦模式（1:先到先得模式；2:按权重分配模式）
* @param maxAllowCount: 允许能抢到麦的最大人数
* @param maxTalkTime: 允许抢到麦后使用麦的最大时间（秒）
* @param voteTime: 抢麦仲裁时间（秒），过了X秒后服务器将进行仲裁谁最终获得麦（仅在按权重分配模式下有效）
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) setGrabMicOption:(NSString*) channelID mode:(int)mode maxAllowCount:(int)maxAllowCount maxTalkTime:(int)maxTalkTime voteTime:(unsigned int)voteTime;

/**
* 功能描述:    发起抢麦活动
* @param pChannelID: 抢麦活动的频道id
* @param pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) startGrabMicAction:(NSString*) channelID strContent:(NSString*) pContent;

/**
* 功能描述:    停止抢麦活动
* @param pChannelID: 抢麦活动的频道id
* @param pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) stopGrabMicAction:(NSString*) channelID strContent:(NSString*) pContent;

/**
* 功能描述:    发起抢麦请求
* @param pChannelID: 抢麦的频道id
* @param score: 积分（权重分配模式下有效，游戏根据自己实际情况设置）
* @param isAutoOpenMic: 抢麦成功后是否自动开启麦克风权限
* @param pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) requestGrabMic:(NSString*) channelID score:(int)score isAutoOpenMic:(bool)isAutoOpenMic strContent:(NSString*) pContent;

/**
* 功能描述:    释放抢到的麦
* @param pChannelID: 抢麦活动的频道id
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) releaseGrabMic:(NSString*) channelID;


//---------------------连麦接口---------------------//
/**
* 功能描述:    连麦相关设置（角色是频道的管理者或者主播时调用此接口进行频道内的连麦设置）
* @param pChannelID: 连麦的频道id
* @param waitTimeout: 等待对方响应超时时间（秒）
* @param maxTalkTime: 最大通话时间（秒）
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) setInviteMicOption:(NSString*) channelID waitTimeout:(int)waitTimeout maxTalkTime:(int)maxTalkTime;

/**
* 功能描述:    发起与某人的连麦请求（主动呼叫）
* @param pUserID: 被叫方的用户id
* @param pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) requestInviteMic:(NSString*) channelID strUserID:(NSString*)pUserID strContent:(NSString*) pContent;

/**
* 功能描述:    对连麦请求做出回应（被动应答）
* @param pUserID: 主叫方的用户id
* @param isAccept: 是否同意连麦
* @param pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) responseInviteMic:(NSString*) pUserID isAccept:(bool)isAccept strContent:(NSString*) pContent;

/**
* 功能描述:    停止连麦
* @return   YOUME_SUCCESS - 成功
*          其他 - 具体错误码
*/
- (YouMeErrorCode_t) stopInviteMic;

/**
 * 功能描述:   向房间广播消息
 * @param channelID: 广播房间
 * @param strContent: 广播内容-文本串
 * @param requestID:返回消息标识，回调的时候会回传该值
 * @return   YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) sendMessage:(NSString*) channelID  strContent:(NSString*) strContent  requestID:(int*) requestID;

/**
 * 功能描述:   对房间设置白名单用户
 * @param channelID: 要设置的房间
 * @param whiteUserList: 白名单用户列表, 以|分隔，如：User1|User2|User3
 * @return   YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setWhiteUserList:(NSString*) channelID  whiteUserList:(NSString*) whiteUserList;

/**
 *  功能描述: 把某人踢出房间
 *  @param  userID: 被踢的用户ID
 *  @param  channelID: 从哪个房间踢出
 *  @param  lastTime: 踢出后，多长时间内不允许再次进入
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) kickOtherFromChannel:(NSString*) userID  channelID:(NSString*)channelID   lastTime:(int) lastTime;

/**
 *  功能描述:设置变声是否可用
 *
 *  @param enabled: 设置变声是否可用，开启时会略微增大声音延迟
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) setMagicVoiceEnable:(bool)enabled;

/**
 *  功能描述:检查设备是否设置了静音，异步回调（），仅IOS有效
 *          这个功能有限制，Ios不支持静音键的情况（比如进入录音模式）下无效。可在进房间前检测。
 *  @return YOUME_SUCCESS - 成功
 *          其他 - 具体错误码
 */
- (YouMeErrorCode_t) checkIsDeviceMute;

 /**
  *  功能描述:设置变声功能参数
  *
  *  @param effectInfo: 由变声管理模块获取到的YMMagicVoiceEffectInfo（变声音效信息），其中的m_param参数，设置时将变声器置为可用
  *  @return YOUME_SUCCESS - 成功
  *          其他 - 具体错误码
  */
 - (YouMeErrorCode_t) setMagicVoiceInfo:(NSString*) effectInfo;

 /**
  *  功能描述:清除变声功能参数
  *
  *  @return YOUME_SUCCESS - 成功
  *          其他 - 具体错误码
  */
 - (YouMeErrorCode_t) clearMagicVoiceInfo;

 /**
  *  功能描述:设置变声参数微调接口
  *
  *  @param dFS: 音色的微调值，范围-1.0f~1.0f，在后台下发的基准值的基础上按百分比调节，值减小音色会变厚重，值增大音色会变尖锐
  *         dSemitones: 音调的微调值，范围-1.0f~1.0f，在后台下发的基准值的基础上按百分比调节，值减小音调会低，值增大音调会变高
  *  @return YOUME_SUCCESS - 成功
  *          其他 - 具体错误码
  */
 - (YouMeErrorCode_t) setMagicVoiceAdjust:(double) dFS dSemitones:(double) dSemitones;

/**
 *  功能描述:变声器效果是否启用
 *
 *  @return 变声器是否可用，为false时表示当前没有变声效果生效，可以不创建变声器
 */
- (bool) getMagicVoiceEffectEnabled;



@end

