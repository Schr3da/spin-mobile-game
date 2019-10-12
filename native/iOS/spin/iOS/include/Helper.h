//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>

@interface Helper : NSObject
    
+(UIColor *)getGrayColor;
+(void)releaseViewObject:(UIView **)view;
+(void)releaseObject:(NSObject **)_object;
+(NSString *)newGameText;
+(NSString *)logoImageName;
+(NSString *)rankingText;
+(NSString *)rankingImageName;
+(NSString *)highscoreIcon;
+(NSString *)leaderboardIcon;
+(NSString *)settingsText;
+(NSString *)settingsImageName;
+(NSString *)backText;
+(NSString *)colorText;
+(NSString *)readyText;
+(NSString *)submitText;
+(NSString *)stageText;
+(NSString *)memorizeText;
+(NSString *)timeText;
+(NSString *)nextLevelText;
+(NSString *)solutionText;
+(NSString *)settingsSoundText;
+(NSString *)settingsVibrationText;
+(NSString *)settingsSnapToGridText;
+(NSString *)settingsLeaderboardText;
+(NSString *)retryText;
+(NSString *)deliverImageName;
+(NSString *)failedImageName;
+(NSString *)menuText;
+(NSString *)continueText;
+(NSString *)restartText;
+(NSString *)actionMenuTitle;
+(NSString *)actionMenuText;
+(NSString *)leaderboardURL;
+(NSString *)tutorialTitle;
+(NSString *)dismissText;
+(NSString *)gameCompleteTitle;
+(NSString *)gameCompleteText;
+(NSArray *)memorizeTutorialTips;
+(NSArray *)placeColorTutorialTips;

+(CGSize)buttonSize;
+(int)seperator;
+(int)screenBorderOffset;
+(int)largeCellHeight;
+(int)smallCellHeight;
+(NSTimeInterval)animationTime;
+(UIColor *)getIUColorFromHex:(int)color;
+(NSMutableArray *)getSettingsConent;
+(NSMutableArray *)getRankingContent;
+(NSMutableArray *)getOverviewContent;
+(NSTimeInterval)timerInterval;
+(void)releaseViewControllerObject:(UIViewController **)controller;
+(void)releaseMutableContainer:(NSMutableArray **)_object;
+(void)removeSubviewsFromParent:(UIView **)view;

@end
