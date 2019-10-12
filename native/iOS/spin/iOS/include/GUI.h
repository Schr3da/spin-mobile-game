//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#import "Scene.h"
#import "PositionFactory.h"
#import "Settings.h"

@class HeaderView;
@class FooterView;
@class SettingsView;
@class RankingView;
@class Overview;
@class SubmenuViewController;
@class TutorialViewController;

@interface GUI : UIView{
    UIViewController *rootControllerRef;
    HeaderView *header;
    FooterView *footer;
    SettingsView *settingsV;
    RankingView *rankingV;
    Overview *overV;
    Settings *settings;
    SubmenuViewController *submenuC;
    TutorialViewController *tutorialC;
    NSTimeInterval timeLimit;
    NSTimer *gametimer;
}

-(instancetype)initWithWindow:(UIWindow *)window ;
-(void)addMenu;
-(void)addSubmenu;
-(void)hideCurrentView:(NSString *)bId;
-(void)setNextColor;
-(void)setCurrentColor;
-(void)updateLabelsWithValue:(NSTimeInterval)value;
-(void)interactWithSubmenu;
-(UIViewController *)rootViewcontroller;
-(void)addGameTimer:(NSTimeInterval) time;

@property (readwrite, assign, nonatomic) Scene *sceneRef;
@property (readonly, assign, nonatomic) ApplicationState &state;
@property (readonly, assign, nonatomic) BOOL isAnimating;

@end
