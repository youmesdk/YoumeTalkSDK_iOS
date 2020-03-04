//
//  YMVoiceService.m
//  YmTalkTestRef
//
//  Created by pinky on 2017/5/27.
//  Copyright © 2017年 Youme. All rights reserved.
//


#import "YMVoiceService.h"
#import "IYouMeVoiceEngine.h"

@implementation MemberChangeOC


@end

class YouMeVoiceImp : public IYouMeEventCallback, public IYouMePcmCallback, public IRestApiCallback, public IYouMeMemberChangeCallback, public IYouMeChannelMsgCallback
{
public:
    virtual void onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * room, const char * param) override ;
   
    virtual void onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;
    virtual void onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;
    virtual void onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;
    
    virtual  void onRequestRestAPI( int requestID, const YouMeErrorCode &iErrorCode, const  char* strQuery, const  char*  strResult )override;
    
    virtual void onMemberChange( const  char* channel, const char* listMemberChange ,bool isUpdate)override;
	
    virtual void onBroadcast(const YouMeBroadcast bc, const  char* channel, const  char* param1, const char* param2, const  char* strContent)override;
};

void YouMeVoiceImp::onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * room, const char * param)
{

    if( [YMVoiceService getInstance].delegate){
        [[YMVoiceService getInstance].delegate onYouMeEvent:event errcode:error
                        roomid:[NSString stringWithCString:room encoding:NSUTF8StringEncoding]
                         param:[NSString stringWithCString:param encoding:NSUTF8StringEncoding]];
    }
}

void YouMeVoiceImp::onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
    id<VoiceEngineCallback> delegate = [YMVoiceService getInstance].delegate;
    //[[YMVoiceService getInstance] youme_dispatch_async_choose:^{
    SEL sel = @selector(onPcmDataRemote:samplingRateHz:bytesPerSample:data:dataSizeInByte:);
    if(delegate && [delegate respondsToSelector:sel])
        [delegate onPcmDataRemote:channelNum samplingRateHz:samplingRateHz bytesPerSample:bytesPerSample data:data dataSizeInByte:dataSizeInByte];
    //}];
}

void YouMeVoiceImp::onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
    id<VoiceEngineCallback> delegate = [YMVoiceService getInstance].delegate;
    //[[YMVoiceService getInstance] youme_dispatch_async_choose:^{
    SEL sel = @selector(onPcmDataRecord:samplingRateHz:bytesPerSample:data:dataSizeInByte:);
    if(delegate && [delegate respondsToSelector:sel])
        [delegate onPcmDataRecord:channelNum samplingRateHz:samplingRateHz bytesPerSample:bytesPerSample data:data dataSizeInByte:dataSizeInByte];
    //}];
}

void YouMeVoiceImp::onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
    id<VoiceEngineCallback> delegate = [YMVoiceService getInstance].delegate;
    //[[YMVoiceService getInstance] youme_dispatch_async_choose:^{
    SEL sel = @selector(onPcmDataMix:samplingRateHz:bytesPerSample:data:dataSizeInByte:);
    if(delegate && [delegate respondsToSelector:sel])
        [delegate onPcmDataMix:channelNum samplingRateHz:samplingRateHz bytesPerSample:bytesPerSample data:data dataSizeInByte:dataSizeInByte];
    //}];
}

void YouMeVoiceImp::onRequestRestAPI( int requestID, const YouMeErrorCode &iErrorCode, const char* strQuery, const char*  strResult )
{
    if( [YMVoiceService getInstance].delegate ){
        NSString* query = [NSString stringWithUTF8String:strQuery];
    	NSString* result = [NSString stringWithUTF8String:strResult];

        
        [[YMVoiceService getInstance].delegate onRequestRestAPI:requestID iErrorCode:iErrorCode  query:query  result:result ];
    }
}

void YouMeVoiceImp::onMemberChange( const char* channel, const char* listMemberChange,bool isUpdate)
{

    if( [YMVoiceService getInstance].delegate ){
        NSString* channelID  = [NSString stringWithUTF8String: channel ];
        
        NSError *jsonDecodeError = nil;
        //{"channelid":"2418video","memchange":[{"isJoin":true,"userid":"1001590"}]}
        NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:[[NSString stringWithUTF8String:listMemberChange] dataUsingEncoding:NSUTF8StringEncoding] options:kNilOptions error:&jsonDecodeError];
        if(dict != nil){
            NSMutableArray<MemberChangeOC*>* arr = [NSMutableArray arrayWithCapacity:15];
            NSArray *songArray = [dict objectForKey:@"memchange"];
            for (int i=0; i<songArray.count; i++) {
                MemberChangeOC* change = [MemberChangeOC new];
                NSDictionary *userInfo = [songArray objectAtIndex:i];
                change.userID = [userInfo objectForKey:@"userid"];
                change.isJoin = [(NSNumber*)[userInfo objectForKey:@"isJoin"] boolValue];
                [arr addObject: change ];
            }
            [[YMVoiceService getInstance].delegate onMemberChange:channelID changeList:[arr copy] isUpdate:isUpdate ];
        }
    }
}

void YouMeVoiceImp::onBroadcast(const YouMeBroadcast bc, const  char* channel, const  char* param1, const  char* param2, const  char* strContent)
{
    if( [YMVoiceService getInstance].delegate ){
        NSString* channelID  = [NSString stringWithUTF8String: channel ];
        NSString* p1  = [NSString stringWithUTF8String: param1 ];
        NSString* p2  = [NSString stringWithUTF8String: param2];
        NSString* content  = [NSString stringWithUTF8String: strContent ];

        
        [[YMVoiceService getInstance].delegate onBroadcast:bc strChannelID:channelID strParam1:p1 strParam2:p2 strContent:content ];
    }
}

static YMVoiceService *s_YMVoiceService_sharedInstance = nil;

@interface YMVoiceService(){
YouMeVoiceImp*  imp;
}
@end

extern void SetServerMode(SERVER_MODE serverMode);

@implementation YMVoiceService
//公共接口
+ (YMVoiceService *)getInstance
{
    @synchronized (self)
    {
        if (s_YMVoiceService_sharedInstance == nil)
        {
            s_YMVoiceService_sharedInstance = [self alloc];
            
            s_YMVoiceService_sharedInstance->imp = new YouMeVoiceImp();
        }
    }
    
    return s_YMVoiceService_sharedInstance;
}

+ (void)destroy
{
    delete s_YMVoiceService_sharedInstance->imp;
}


- (void)setTestServer:(bool) isTest{
    if(isTest)
    {
        SetServerMode(SERVER_MODE_TEST);
    }else
    {
        SetServerMode(SERVER_MODE_FORMAL);
    }
}


- (int)initSDK:(id<VoiceEngineCallback>)delegate  appkey:(NSString*)appKey  appSecret:(NSString*)appSecret
        regionId:(YOUME_RTC_SERVER_REGION)regionId  serverRegionName:(NSString*) serverRegionName
{
    self.delegate = delegate;
    IYouMeVoiceEngine::getInstance()->setMemberChangeCallback( self->imp );
    IYouMeVoiceEngine::getInstance()->setRestApiCallback( self->imp );
    IYouMeVoiceEngine::getInstance()->setNotifyCallback( self->imp );
	
    return IYouMeVoiceEngine::getInstance()->init( self->imp, [appKey UTF8String], [appSecret UTF8String],
                                                  ( YOUME_RTC_SERVER_REGION )regionId , [serverRegionName UTF8String]);
}


- (int)unInit
{
    return IYouMeVoiceEngine::getInstance ()->unInit ();
}

//开启测试服
//-(void)setTestServer:(bool)isTest
//{
//    return IYouMeVoiceEngine::getInstance()->setTestServer(isTest);
//}

-(void)setServerRegion:(YOUME_RTC_SERVER_REGION)serverRegionId regionName:(NSString*)regionName bAppend:(bool)bAppend
{
    return IYouMeVoiceEngine::getInstance()->setServerRegion( ( YOUME_RTC_SERVER_REGION )serverRegionId, [regionName UTF8String], bAppend);
}

//切换语音输出设备，bOutputToSpeaker:true——扬声器，false——听筒，默认为true
- (YouMeErrorCode)setOutputToSpeaker:(bool)bOutputToSpeaker
{
    return IYouMeVoiceEngine::getInstance ()->setOutputToSpeaker(bOutputToSpeaker);
}

//设置扬声器静音,mute:true——静音，false——取消静音
-(void)setSpeakerMute:(bool)mute
{
    return IYouMeVoiceEngine::getInstance()->setSpeakerMute(mute);
}

//获取扬声器静音状态,return true——静音，false——没有静音
-(bool)getSpeakerMute
{
    return IYouMeVoiceEngine::getInstance()->getSpeakerMute();
}

//获取麦克风静音状态,return true——静音，false——没有静音
-(bool)getMicrophoneMute
{
    return IYouMeVoiceEngine::getInstance()->getMicrophoneMute();
}

//设置麦克风静音,mute:true——静音，false——取消静音
-(void)setMicrophoneMute:(bool)mute
{
    return IYouMeVoiceEngine::getInstance()->setMicrophoneMute(mute);
}


-(void) setOtherMicMute:(NSString *)strUserID  mute:(bool) mute
{
    IYouMeVoiceEngine::getInstance()->setOtherMicMute( [strUserID UTF8String], mute);
}
-(void) setOtherSpeakerMute: (NSString *)strUserID  mute:(bool) mute
{
    IYouMeVoiceEngine::getInstance()->setOtherSpeakerMute([strUserID UTF8String],mute);
}
-(void) setListenOtherVoice: (NSString *)strUserID  isOn:(bool) isOn
{
    IYouMeVoiceEngine::getInstance()->setListenOtherVoice([strUserID UTF8String],isOn);
}

//获取当前音量大小
- (unsigned int)getVolume
{
    return IYouMeVoiceEngine::getInstance ()->getVolume ();
}

//设置音量
- (void)setVolume:(unsigned int)uiVolume
{
    IYouMeVoiceEngine::getInstance ()->setVolume(uiVolume);
}

//获取当前麦克风音量增益大小
- (unsigned int)getMicVolume
{
    return IYouMeVoiceEngine::getInstance ()->getMicVolume ();
}
//设置麦克风音量增益
- (void)setMicVolume:(unsigned int)uiVolume
{
    IYouMeVoiceEngine::getInstance ()->setMicVolume(uiVolume);
}

-(void)setAutoSendStatus:(bool)bAutoSend{
    IYouMeVoiceEngine::getInstance ()->setAutoSendStatus( bAutoSend );
}

//多人语音接口

//加入音频会议
- (YouMeErrorCode)joinChannelSingleMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole)userRole checkRoomExist:(bool)checkRoomExist
{
    return IYouMeVoiceEngine::getInstance()->joinChannelSingleMode([strUserID UTF8String],[strChannelID UTF8String], userRole, checkRoomExist);
}

- (YouMeErrorCode)joinChannelSingleMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole)userRole
{
    return IYouMeVoiceEngine::getInstance()->joinChannelSingleMode([strUserID UTF8String],[strChannelID UTF8String], userRole, false);
}

- (YouMeErrorCode)joinChannelMultiMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole)userRole checkRoomExist:(bool)checkRoomExist
{
    return IYouMeVoiceEngine::getInstance()->joinChannelMultiMode([strUserID UTF8String],[strChannelID UTF8String], userRole, checkRoomExist);
}

- (YouMeErrorCode)joinChannelMultiMode:(NSString *)strUserID channelID:(NSString *)strChannelID userRole:(YouMeUserRole)userRole
{
    return IYouMeVoiceEngine::getInstance()->joinChannelMultiMode([strUserID UTF8String],[strChannelID UTF8String], userRole, false);
}

- (YouMeErrorCode) speakToChannel:(NSString *)strChannelID{
    return IYouMeVoiceEngine::getInstance()->speakToChannel( [ strChannelID UTF8String ]);
}

//退出音频会议
- (YouMeErrorCode)leaveChannelMultiMode:(NSString *)strChannelID
{
    
    return IYouMeVoiceEngine::getInstance ()->leaveChannelMultiMode ([strChannelID UTF8String]);
}

- (YouMeErrorCode)leaveChannelAll
{
    
    return IYouMeVoiceEngine::getInstance ()->leaveChannelAll ();
}

//是否使用移动网络,默认不用
- (void)setUseMobileNetworkEnabled:(bool)bEnabled
{
    IYouMeVoiceEngine::getInstance ()->setUseMobileNetworkEnabled (bEnabled);
}

- (bool) getUseMobileNetworkEnabled{
    return IYouMeVoiceEngine::getInstance ()->getUseMobileNetworkEnabled();
}

- (void)setToken:(NSString*) token
{
    IYouMeVoiceEngine::getInstance()->setToken( [token UTF8String ]);
}

- (YouMeErrorCode)playBackgroundMusic:(NSString *)path   repeat:(bool)repeat
{
    return IYouMeVoiceEngine::getInstance ()->playBackgroundMusic([path UTF8String], repeat );
}

- (YouMeErrorCode)pauseBackgroundMusic
{
    return IYouMeVoiceEngine::getInstance()->pauseBackgroundMusic();
}

- (YouMeErrorCode)resumeBackgroundMusic
{
    return IYouMeVoiceEngine::getInstance()->resumeBackgroundMusic();
}

- (YouMeErrorCode)stopBackgroundMusic
{
    return IYouMeVoiceEngine::getInstance()->stopBackgroundMusic();
}

- (YouMeErrorCode)setBackgroundMusicVolume:(unsigned int)bgVolume
{
    return IYouMeVoiceEngine::getInstance()->setBackgroundMusicVolume(bgVolume);
}

- (int)getBackgroundMusicVolume
{
    return IYouMeVoiceEngine::getInstance()->getBackgroundMusicVolume();
}

- (int)getBgmProgress
{
    return IYouMeVoiceEngine::getInstance()->getBgmProgress();
}

- (void)setBgmProgress:(unsigned int)bgmProgress
{
    IYouMeVoiceEngine::getInstance()->setBgmProgress(bgmProgress);
}

- (YouMeErrorCode)setEffectVolume:(unsigned int)effectVolume
{
    return IYouMeVoiceEngine::getInstance()->setEffectVolume(effectVolume);
}

- (int)getEffectVolume
{
    return IYouMeVoiceEngine::getInstance()->getEffectVolume();
}

- (YouMeErrorCode_t)playEffect:(NSString *)path  repeatCount:(int)repeatCount effectId:(int*)effectId
{
    return IYouMeVoiceEngine::getInstance()->playEffect( [path UTF8String], repeatCount, effectId );
}

- (YouMeErrorCode_t)stopEffect:(int)effectId
{
    return IYouMeVoiceEngine::getInstance()->stopEffect( effectId );
}


- (YouMeErrorCode_t)stopAllEffects
{
    return IYouMeVoiceEngine::getInstance()->stopAllEffects();
}

- (YouMeErrorCode_t) pauseEffect:(int) effectId
{
    return IYouMeVoiceEngine::getInstance()->pauseEffect( effectId );
}

- (YouMeErrorCode_t) resumeEffect:(int) effectId
{
    return IYouMeVoiceEngine::getInstance()->resumeEffect( effectId );
}

- (YouMeErrorCode_t) pauseAllEffects
{
    return IYouMeVoiceEngine::getInstance()->pauseAllEffects( );
}

- (YouMeErrorCode_t) resumeAllEffects
{
    return IYouMeVoiceEngine::getInstance()->resumeAllEffects( );
}

//获取SDK版本号
- (int)getSDKVersion
{
    return IYouMeVoiceEngine::getInstance ()->getSDKVersion();
}

//  功能描述: 设置是否将麦克风声音旁路到扬声器输出，可以为主播等提供监听自己声音和背景音乐的功能
- (YouMeErrorCode_t)setHeadsetMonitorMicOn:(bool)micEnabled
{
    return IYouMeVoiceEngine::getInstance()->setHeadsetMonitorOn(micEnabled);
}

//  功能描述: 设置是否用耳机监听自己的声音或背景音乐，可以为主播等提供监听自己声音和背景音乐的功能
- (YouMeErrorCode)setHeadsetMonitorMicOn:(bool)micEnabled BgmOn:(bool)bgmEnabled
{
    return IYouMeVoiceEngine::getInstance()->setHeadsetMonitorOn(micEnabled, bgmEnabled);
}

//  功能描述: 设置主播是否开启混响模式
- (YouMeErrorCode)setReverbEnabled:(bool)enabled
{
    return IYouMeVoiceEngine::getInstance()->setReverbEnabled(enabled);
}

//  功能描述: 设置主播是否开启混响模式
- (YouMeErrorCode)setAudioEffectType:(int)effectType
{
    return IYouMeVoiceEngine::getInstance()->setAudioEffectType(effectType);
}

- (YouMeErrorCode)setVadCallbackEnabled:(bool)enabled
{
    return IYouMeVoiceEngine::getInstance()->setVadCallbackEnabled(enabled);
}

- (YouMeErrorCode) setMicLevelCallback:(int) maxLevel{
    return IYouMeVoiceEngine::getInstance()->setMicLevelCallback(maxLevel);
}

- (YouMeErrorCode) setFarendVoiceLevelCallback:(int) maxLevel{
    return IYouMeVoiceEngine::getInstance()->setFarendVoiceLevelCallback(maxLevel);
}

- (YouMeErrorCode) setReleaseMicWhenMute:(bool) enabled{
    return IYouMeVoiceEngine::getInstance()->setReleaseMicWhenMute(enabled);
}

- (YouMeErrorCode_t) setExitCommModeWhenHeadsetPlugin:(bool) enabled{
    return IYouMeVoiceEngine::getInstance()->setExitCommModeWhenHeadsetPlugin(enabled);
}

- (YouMeErrorCode_t) setChannelAudioMode: (ChannelAudioMode_t) audioMode
{
    return IYouMeVoiceEngine::getInstance()->setChannelAudioMode(audioMode);
}

- (YouMeErrorCode_t) setExternalSoundCardMode:(bool) isExternalSoundCard
{
    return IYouMeVoiceEngine::getInstance()->setExternalSoundCardMode(isExternalSoundCard);
}

- (YouMeErrorCode_t) setForceDisableAEC:(bool) disable
{
    return IYouMeVoiceEngine::getInstance()->setForceDisableAEC(disable);
}

- (YouMeErrorCode_t) setForceDisableAGC:(bool) disable
{
    return IYouMeVoiceEngine::getInstance()->setForceDisableAGC(disable);
}

- (void) setRecordingTimeMs:(unsigned int)timeMs
{
    return IYouMeVoiceEngine::getInstance()->setRecordingTimeMs(timeMs);
}

- (void) setPlayingTimeMs:(unsigned int)timeMs
{
    return IYouMeVoiceEngine::getInstance()->setPlayingTimeMs(timeMs);
}

- (float) getSoundtouchPitchSemiTones
{
    return IYouMeVoiceEngine::getInstance()->getSoundtouchPitchSemiTones();
}

- (int) setSoundtouchPitchSemiTones:(float) fPitchSemiTones
{
    return IYouMeVoiceEngine::getInstance()->setSoundtouchPitchSemiTones(fPitchSemiTones);
}

- (YouMeErrorCode)pauseChannel
{
    return IYouMeVoiceEngine::getInstance ()->pauseChannel();
}


- (YouMeErrorCode_t)requestRestApi:(NSString*) strCommand strQueryBody:(NSString*) strQueryBody requestID:(int*)requestID{
    return IYouMeVoiceEngine::getInstance()->requestRestApi( [strCommand UTF8String], [strQueryBody UTF8String], requestID   );
}

- (YouMeErrorCode_t)setUserRole:(YouMeUserRole_t) eUserRole {
    return IYouMeVoiceEngine::getInstance()->setUserRole(eUserRole);
}

- (YouMeUserRole_t) getUserRol {
    return IYouMeVoiceEngine::getInstance()->getUserRole();
}

- (YouMeErrorCode) getChannelUserList:(NSString*) channelID maxCount:(int)maxCount notifyMemChange:(bool)notifyMemChange {
    return IYouMeVoiceEngine::getInstance()->getChannelUserList([channelID UTF8String], maxCount, notifyMemChange );
}

- (YouMeErrorCode_t) setPcmCallbackEnable:(int) flag
{
    return IYouMeVoiceEngine::getInstance()->setPcmCallbackEnable( self->imp, flag);
}

- (YouMeErrorCode)resumeChannel
{
    return IYouMeVoiceEngine::getInstance ()->resumeChannel();
}

- (YouMeErrorCode_t) setGrabMicOption:(NSString*) channelID mode:(int)mode maxAllowCount:(int)maxAllowCount maxTalkTime:(int)maxTalkTime voteTime:(unsigned int)voteTime
{
	return IYouMeVoiceEngine::getInstance ()->setGrabMicOption([channelID UTF8String], mode, maxAllowCount, maxTalkTime, voteTime);
}

- (YouMeErrorCode_t) startGrabMicAction:(NSString*) channelID strContent:(NSString*) pContent
{
	return IYouMeVoiceEngine::getInstance ()->startGrabMicAction([channelID UTF8String], [pContent UTF8String]);
}

- (YouMeErrorCode_t) stopGrabMicAction:(NSString*) channelID strContent:(NSString*) pContent
{
	return IYouMeVoiceEngine::getInstance ()->stopGrabMicAction([channelID UTF8String], [pContent UTF8String]);
}

- (YouMeErrorCode_t) requestGrabMic:(NSString*) channelID score:(int)score isAutoOpenMic:(bool)isAutoOpenMic strContent:(NSString*) pContent
{
	return IYouMeVoiceEngine::getInstance ()->requestGrabMic([channelID UTF8String], score, isAutoOpenMic, [pContent UTF8String]);
}

- (YouMeErrorCode_t) releaseGrabMic:(NSString*) channelID
{
	return IYouMeVoiceEngine::getInstance ()->releaseGrabMic([channelID UTF8String]);
}

- (YouMeErrorCode_t) setInviteMicOption:(NSString*) channelID waitTimeout:(int)waitTimeout maxTalkTime:(int)maxTalkTime
{
	return IYouMeVoiceEngine::getInstance ()->setInviteMicOption([channelID UTF8String], waitTimeout, maxTalkTime);
}

- (YouMeErrorCode_t) requestInviteMic:(NSString*) channelID strUserID:(NSString*)pUserID strContent:(NSString*) pContent
{
	return IYouMeVoiceEngine::getInstance ()->requestInviteMic([channelID UTF8String], [pUserID UTF8String], [pContent UTF8String]);
}

- (YouMeErrorCode_t) responseInviteMic:(NSString*) pUserID isAccept:(bool)isAccept strContent:(NSString*) pContent
{
	return IYouMeVoiceEngine::getInstance ()->responseInviteMic([pUserID UTF8String], isAccept, [pContent UTF8String]);
}

- (YouMeErrorCode_t) stopInviteMic
{
	return IYouMeVoiceEngine::getInstance ()->stopInviteMic();
}

- (YouMeErrorCode_t) sendMessage:(NSString*) channelID  strContent:(NSString*) strContent  requestID:(int*) requestID{
    return IYouMeVoiceEngine::getInstance ()->sendMessage( [channelID UTF8String], [strContent UTF8String], requestID );
}

- (YouMeErrorCode_t) setWhiteUserList:(NSString*) channelID  whiteUserList:(NSString*) whiteUserList
{
    NSArray* array = [whiteUserList componentsSeparatedByString:@"|"];
    int count= (int)array.count;
    std::vector<std::string> vecWhiteUserList;
    for(int i = 0; i < count; i++)
    {
        vecWhiteUserList.push_back([[array objectAtIndex:i] UTF8String]);
    }
    
    return IYouMeVoiceEngine::getInstance ()->setWhiteUserList([channelID UTF8String], vecWhiteUserList);
}

- (YouMeErrorCode_t) kickOtherFromChannel:(NSString*) userID  channelID:(NSString*)channelID   lastTime:(int) lastTime
{
    return IYouMeVoiceEngine::getInstance ()->kickOtherFromChannel( [userID UTF8String],[channelID UTF8String], lastTime  );
}

- (YouMeErrorCode_t) setMagicVoiceEnable:(bool)enabled
{
    return IYouMeVoiceEngine::getInstance ()->setMagicVoiceEnable( enabled );
}

- (YouMeErrorCode_t) checkIsDeviceMute
{
    return IYouMeVoiceEngine::getInstance ()->checkIsDeviceMute();
}

 - (YouMeErrorCode_t) setMagicVoiceInfo:(NSString*) effectInfo
 {
     return IYouMeVoiceEngine::getInstance ()->setMagicVoiceInfo( [effectInfo UTF8String] );
 }

 - (YouMeErrorCode_t) clearMagicVoiceInfo
 {
     return IYouMeVoiceEngine::getInstance ()->clearMagicVoiceInfo();
 }

 - (YouMeErrorCode_t) setMagicVoiceAdjust:(double) dFS dSemitones:(double) dSemitones
 {
     return IYouMeVoiceEngine::getInstance ()->setMagicVoiceAdjust(dFS, dSemitones);
 }

- (bool) getMagicVoiceEffectEnabled
{
    return IYouMeVoiceEngine::getInstance ()->getMagicVoiceEffectEnabled();
}

@end


