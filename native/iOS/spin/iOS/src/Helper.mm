//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "Helper.h"
#import "PositionFactory.h"
#import "Settings.h"
#import "SettingsContent.h"
#import "OverviewContent.h"
#import "RankingContent.h"

@implementation Helper

+(UIColor *)getGrayColor{
    return [UIColor colorWithRed:0.424f green:0.478f blue:0.537f alpha:1.f];
}

+(void)releaseViewObject:(UIView **)view{
    UIView *object = *view;
    if(object != nil){
        [object removeFromSuperview];
        [object release];
    }
    object = nil;
    *view = object;
}

+(void)releaseObject:(NSObject **)_object{
    NSObject *object = *_object;
    if(object != nil){
        [object release];
    }
    object = nil;
    *_object = object;
}

+(void)releaseMutableContainer:(NSMutableArray **)_object{
    NSMutableArray *object = *_object;
    if(object != nil){
        [object removeAllObjects];
        [object release];
    }
    object = nil;
    *_object = object;
}

+(void)releaseViewControllerObject:(UIViewController **)controller{
    UIViewController *object = *controller;
    if(object != nil){
        [object.view removeFromSuperview];
        [object release];
    }
    object = nil;
    *controller = object;
}

+(void)removeSubviewsFromParent:(UIView **)view{
    UIView *object = *view;
    if(object == nil){
        return;
    }
    for (UIView *obj in object.subviews){
        if(obj != nil){
            [obj removeFromSuperview];
            obj = nil;
        }
    }
    object = nil;
    *view = object;
}

+(NSString *)newGameText{
    return @"Play";
}

+(NSString *)readyText{
    return @"Ready";
}

+(NSString *)menuText{
    return @"Menu";
}

+(NSString *)continueText{
    return @"Continue";
}

+(NSString *)restartText{
    return @"Restart";
}

+(NSString *)submitText{
    return @"Submit";
}

+(NSString *)logoImageName{
    return @"logo";
}

+(NSString *)rankingText{
    return @"Ranking";
}

+(NSString *)rankingImageName{
    return @"ranking";
}

+(NSString *)highscoreIcon{
    return @"scoreIcon";
}

+(NSString *)leaderboardIcon{
    return @"leaderboardIcon";
}

+(NSString *)colorText{
    return @"Color";
}

+(NSString *)settingsText{
    return @"Settings";
}

+(NSString *)nextLevelText{
    return @"Next";
}

+(NSString *)solutionText{
    return @"Solution";
}

+(NSString *)actionMenuTitle{
    return @"Actionmenu";
}

+(NSString *)actionMenuText{
    return @"Attention, the game doesn't stop and continues in background.";
}

+(NSString *)gameCompleteText{
    return @"You successfully passed the last level. We want to thank you for playing this game. We hope you had an enjoyable time. Thank you & best regards Georg & Severi ";
}

+(NSString *)gameCompleteTitle{
    return @"Congratulation";
}

+(NSString *)settingsImageName{
    return @"settings";
}

+(NSString *)backText{
    return @"Menu";
}

+(NSString *)stageText{
    return @"Stage";
}

+(NSString *)memorizeText{
    return @"Time to\nmemorize";
}

+(NSString *)timeText{
    return @"Time";
}

+(NSString *)settingsSoundText{
    return @"Sound";
}

+(NSString *)settingsVibrationText{
    return @"Vibration";
}

+(NSString *)settingsSnapToGridText{
    return @"Snap to grid";
}

+(NSString *)settingsLeaderboardText{
    return @"Global leaderboard";
}

+(NSString *)retryText{
    return @"Retry";
}

+(NSString *)deliverImageName{
    return @"delivered";
}

+(NSString *)failedImageName{
    return @"failed";
}

+(NSString *)leaderboardURL{
    return  @"http://spin-gmdev.rhcloud.com/stats";
}

+(NSString *)tutorialTitle{
    return @"Step";
}

+(NSString *)dismissText{
    return @"Dismiss";
}

+(NSArray *)memorizeTutorialTips{
    return [NSArray arrayWithObjects: @"...use your finger to swipe and \nrotate the cube around",
                                      @"...memorize colors and their location... \nyou need to place them soon",
                                      @"...grey surfaces are helpers... \nyou don't need to remember them",
                                      @"...press ready in case you \nare already ready",
                                      @"...time is running...\npress dismiss to hide",
            nil];
}

+(NSArray *)placeColorTutorialTips{
    return [NSArray arrayWithObjects: @"...now you need to place the colors \naccording to their location",
                                      @"...change the color by pressing \nonto the colorbox at the top",
                                      @"...tap on a surface \nto place a color successfully",
                                      @"...double tap to remove the color \nfrom its surface",
                                      @"...in case the colorbox is empty \n all colors got placed",
                                      @"...time is running...\npress dismiss to hide",
            nil];
}

+(CGSize)buttonSize{
    CGSize size = [UIScreen mainScreen].bounds.size;
    size.height = (int)(size.height * 0.07 * 1.2);
    size.width = (int)(size.width * 0.2);
    return size;
}

+(int)seperator{
    return [UIScreen mainScreen].bounds.size.width*0.1;
}

+(int)largeCellHeight{
    return 64;
}

+(int)smallCellHeight{
    return 44;
}

+(int)screenBorderOffset{
    return 20;
}

+(NSTimeInterval)timerInterval{
    return 1.f;
}

+(NSTimeInterval)animationTime{
    return 0.5f;
}

+(UIColor *)getIUColorFromHex:(int)color{
    return [UIColor colorWithRed:((float)((color & 0xFF0000) >> 16))/255.0 \
                           green:((float)((color & 0x00FF00) >>  8))/255.0 \
                            blue:((float)((color & 0x0000FF) >>  0))/255.0 \
                           alpha:1.0];
}

+(NSMutableArray *)getSettingsConent{
    Settings &settings = PositionFactory::instance().getSettings();
    NSMutableArray *datas = [[[NSMutableArray alloc]init]autorelease];
    //[self addSettingsContentWithTitle:@"Sound" information:[self settingsSoundText] selectedImageName:@"soundIcon" unselectedImageName:@"nosoundIcon" selected:settings.getSoundActive() color:settings.getBlueColor() container:&datas];
    [self addSettingsContentWithTitle:@"Vibration" information:[self settingsVibrationText] selectedImageName:@"vibrationIcon" unselectedImageName:@"novibrationIcon" selected:settings.getVibrationActive() color:settings.getRedColor() container:&datas];
    [self addSettingsContentWithTitle:@"Grid" information:[self settingsSnapToGridText] selectedImageName:@"snapToGridIcon" unselectedImageName:@"nosnapToGridIcon" selected:settings.getSnapToGrid() color:settings.getGreenColor() container:&datas];
    [self addSettingsContentWithTitle:@"Tutorial" information:[self tutorialTitle] selectedImageName:@"networkIcon" unselectedImageName:@"nonetworkIcon" selected:settings.isTutorialActivated() color:settings.getYellowColor() container:&datas];
    return datas;
}

+(void)addSettingsContentWithTitle:(NSString *)title information:(NSString *)information selectedImageName:(NSString *)selectedImageName unselectedImageName:(NSString *)unselectedImageName selected:(bool)selected color:(int)color container:(NSMutableArray **)container{
    NSMutableArray *arrayRef = *container;
    SettingsContent *content = [[SettingsContent alloc]init];
    content.title = title;
    content.information = information;
    content.selectedImageName = selectedImageName;
    content.unselectedImageName = unselectedImageName;
    content.selected = selected;
    content.color = color;
    [arrayRef addObject:content];
    [content release];
    content = nil;
}

+(NSMutableArray *)getRankingContent{
    Settings &settings = PositionFactory::instance().getSettings();
    NSMutableArray *datas = [[[NSMutableArray alloc]init]autorelease];
    int score = settings.getHightscore();
    if(score <= 0){
        [self addRankingContentWithTitle:@"Highscore" value: @"-" color:settings.getBlueColor() imageName:[Helper highscoreIcon] container:&datas];
    } else {
        [self addRankingContentWithTitle:@"Highscore" value: [NSString stringWithFormat:@"%d", score] color:settings.getBlueColor() imageName:[Helper highscoreIcon] container:&datas];
    }
    
    [self addRankingContentWithTitle:@"Leaderboard" value:@"..." color:settings.getRedColor() imageName:[Helper leaderboardIcon] container:&datas];
    return datas;
}

+(void)addRankingContentWithTitle:(NSString *)title value:(NSString *)value color:(int)color imageName:(NSString *)image container:(NSMutableArray **)container{
    NSMutableArray *arrayRef = *container;
    RankingContent *content = [[RankingContent alloc]init];
    content.title = title;
    content.value = value;
    content.color = color;
    content.imageName = image;
    [arrayRef addObject:content];
    [content release];
    content = nil;
}

+(NSMutableArray *)getOverviewContent{
    NSMutableArray *datas = [[[NSMutableArray alloc]init]autorelease];
    Settings &settings = PositionFactory::instance().getSettings();
    [self addOverviewContentWithTitle:@"Archieved" value:[NSString stringWithFormat:@"%d", settings.getCurArchievement()] imageName:@"leaderboardIcon" color:settings.getArchievementColor() container:&datas];
    [self addOverviewContentWithTitle:@"Required" value:[NSString stringWithFormat:@"%d", settings.getRequiredArchievement()] imageName:@"requiredIcon" color:settings.getGrayColor() container:&datas];
    if(settings.isLvlPassed() && !settings.isTutorialActivated()){
         [self addOverviewContentWithTitle:@"Bonus" value:[NSString stringWithFormat:@"%d", settings.getTimeBonus()] imageName:@"timebonusIcon" color:settings.getYellowColor() container:&datas];
    }
    [self addOverviewContentWithTitle:@"Score" value:[NSString stringWithFormat:@"%d", settings.getCurScore()] imageName:@"scoreIcon" color:settings.getBlueColor() container:&datas];
    return datas;
}

+(void)addOverviewContentWithTitle:(NSString *)title value:(NSString *)value imageName:(NSString *)imageName color:(int)color container:(NSMutableArray **)container{
    NSMutableArray *arrayRef = *container;
    OverviewContent *content = [[OverviewContent alloc]init];
    content.title = title;
    content.value = value;
    content.imageName = imageName;
    content.color = color;
    [arrayRef addObject:content];
    [content release];
    content = nil;
}

@end
