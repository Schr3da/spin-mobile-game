//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "GUI.h"
#import "HeaderView.h"
#import "FooterView.h"
#import "Helper.h"
#import "Global.h"
#import "SettingsView.h"
#import "RankingView.h"
#import "Overview.h"
#import "SubmenuViewController.h"
#import "TutorialViewController.h"

@implementation GUI
@synthesize sceneRef;
@synthesize state;
@synthesize isAnimating;

-(instancetype)initWithWindow:(UIWindow *)window{
    self = [super initWithFrame:[UIScreen mainScreen].bounds];
    if(self){
        self.sceneRef = NULL;
        settings = NULL;
        header = nil;
        footer = nil;
        settingsV = nil;
        overV = nil;
        rankingV = nil;
        settingsV = nil;
        timeLimit = 0;
        gametimer = nil;
        settings = &PositionFactory::instance().getSettings();
        rootControllerRef = window.rootViewController;
        isAnimating = false;
        [window.rootViewController.view addSubview:self];
        [self initSubViews];
        [self runWelcomeAnimation];
    }
    return self;
}

-(void)initSubViews{
    [self addMenu];
    [self addSettingsMenu];
    [self addRankingMenu];
    [self addOverview];
    [self addSubmenu];
}

-(void)addMenu{
    int offset = [Helper screenBorderOffset];
    CGSize buttonSize = [Helper buttonSize];
    
    [Helper releaseViewObject: &header];
    header = [[HeaderView alloc]initWithFrame:CGRectMake(0, 0, self.frame.size.width, buttonSize.height*0.8 + offset)];
    [header loadImageNamed:[Helper logoImageName]];
    [self addSubview:header];
    
    [Helper releaseViewObject: &footer];
    footer = [[FooterView alloc]initWithFrame:CGRectMake(0,
                                                         self.frame.size.height - buttonSize.height - offset,
                                                         self.frame.size.width,
                                                         buttonSize.height)];
    [self addSubview:footer];
}

-(void)addSettingsMenu{
    if(header == nil){
        NSLog(@"Make sure to call addMenu method first");
        return;
    }
    [Helper releaseViewObject:&settingsV];
    settingsV = [[SettingsView alloc]initWithFrame:CGRectMake(0,
                                                             header.frame.size.height + header.frame.origin.y*2 - [Helper screenBorderOffset],
                                                             header.frame.size.width,
                                                             self.frame.size.height - header.frame.size.height - header.frame.origin.y*2 - [Helper screenBorderOffset])];
    [self addSubview:settingsV];
    settingsV.frame = CGRectMake(settingsV.frame.origin.x,
                                 self.frame.size.height - settingsV.frame.size.height + settingsV.frame.size.height,
                                 settingsV.frame.size.width,
                                 settingsV.frame.size.height);
    
    settingsV.backgroundColor = [UIColor whiteColor];
    settingsV.alpha = 0.95;
}

-(void)addRankingMenu{
    if(header == nil){
        NSLog(@"Make sure to call addMenu method first");
        return;
    }
    [Helper releaseViewObject:&rankingV];
    rankingV = [[RankingView alloc]initWithFrame:CGRectMake(0,
                                                              header.frame.size.height + header.frame.origin.y*2 + [Helper screenBorderOffset],
                                                              header.frame.size.width,
                                                              self.frame.size.height - header.frame.size.height - header.frame.origin.y*2 - [Helper screenBorderOffset])];
    [self addSubview:rankingV];
    rankingV.frame = CGRectMake(rankingV.frame.origin.x,
                                 self.frame.size.height - rankingV.frame.size.height + rankingV.frame.size.height,
                                 rankingV.frame.size.width,
                                 rankingV.frame.size.height);
    
    rankingV.backgroundColor = [UIColor whiteColor];
    rankingV.alpha = 0.95;
}

-(void)addOverview{
    if(header == nil){
        NSLog(@"Make sure to call addMenu method first");
        return;
    }
    [Helper releaseViewObject:&overV];
    overV = [[Overview alloc]initWithFrame:CGRectMake(0,
                                                        header.frame.size.height + header.frame.origin.y*2 + [Helper screenBorderOffset],
                                                        header.frame.size.width,
                                                        self.frame.size.height - header.frame.size.height - header.frame.origin.y*2 - [Helper screenBorderOffset])];
    [self addSubview:overV];
    overV.frame = CGRectMake(overV.frame.origin.x,
                             self.frame.size.height - overV.frame.size.height + overV.frame.size.height,
                             overV.frame.size.width,
                             overV.frame.size.height);
    
    overV.backgroundColor = [UIColor clearColor];
    overV.alpha = 0.95;
}

-(void)addSubmenu{
    
    [Helper releaseViewControllerObject:&submenuC];
    submenuC = [[SubmenuViewController alloc]init];
    [self addSubview:submenuC.view];
}

-(void)interactWithSubmenu{
    if(submenuC == nil){
        [self addSubmenu];
    }
    if(tutorialC != nil && tutorialC.isVisible){
        return;
    }
    CGRect subframe = submenuC.view.frame;
    subframe.origin.y = (subframe.origin.y == 0) ? self.frame.size.height : 0;
    [UIView animateWithDuration:[Helper animationTime] animations:^{
        submenuC.view.frame = subframe;
    } completion:^(BOOL finished) {
        submenuC.isSubViewDisplayed = !submenuC.isSubViewDisplayed;
    }];
}

-(void)runWelcomeAnimation{
    if(header == nil || footer == nil){
        return;
    }
    int offset = [Helper screenBorderOffset];
    CGSize buttonSize = [Helper buttonSize];
    CGRect headerFrame = CGRectMake(0, 0, self.frame.size.width, buttonSize.height*0.8 + offset);
    CGRect footerFrame = CGRectMake(0,
                                   self.frame.size.height - buttonSize.height - offset,
                                   self.frame.size.width,
                                    buttonSize.height);

    header.frame = CGRectMake(0, -(buttonSize.height*0.8 + offset), self.frame.size.width, buttonSize.height*0.8 + offset);
    footer.frame = CGRectMake(0,
                              self.frame.size.height + buttonSize.height + offset,
                              self.frame.size.width,
                              buttonSize.height);
    [UIView animateWithDuration:[Helper animationTime] animations:^{
        header.frame = headerFrame;
        footer.frame = footerFrame;
    }];
}

-(BOOL)isNotNilForSpecificGameState{
    if(sceneRef == NULL || settings == NULL || header == nil || settings->getApplicationState() != GAME_PLACE_COLORS){
        return false;
    }
    return true;
}

-(void)hideCurrentView:(NSString *)bId{
    [self clearTimer];
    if(settings == NULL){
        return;
    }
    state = settings->getApplicationState();
    if(state == MAIN_MENU){
        if([bId isEqualToString:[Helper newGameText]]){
            [self animateTopView:header bottomView:footer buttonId:bId];
        }
        else if([bId isEqualToString:[Helper settingsText]]){
            [settingsV addContentView];
            [self animateTopView:header bottomView:footer buttonId:bId];
        }
        else if([bId isEqualToString:[Helper rankingText]]){
            [rankingV addContentView];
            [self animateTopView:header bottomView:footer buttonId:bId];
        }
    }
    else if (state == SETTINGS){
        if([bId isEqualToString:[Helper backText]]){
            [self animateTopView:header bottomView:settingsV buttonId:bId];
        }
    }
    else if (state == RANKINGS){
        if([bId isEqualToString:[Helper backText]]){
            [self animateTopView:header bottomView:rankingV buttonId:bId];
        }
    }
    else if(state == GAME_MEMORIZE){
        if([bId isEqualToString:[Helper readyText]] || [bId isEqualToString:[Helper restartText]]){
            [self animateTopView:header bottomView:footer buttonId:bId];
        }
        else { [self didInteractWithSubmenu:bId]; }
    }
    else if(state == GAME_PLACE_COLORS || [bId isEqualToString:[Helper restartText]]){
        if([bId isEqualToString:[Helper submitText]]){
            [self animateTopView:header bottomView:footer buttonId:bId];
        }
        else { [self didInteractWithSubmenu:bId]; }
    }
    else if (state == GAME_RESULT){
        if([bId isEqualToString:[Helper backText]] || [bId isEqualToString:[Helper retryText]] || [bId isEqualToString:[Helper nextLevelText]]){
            [self animateTopView:header bottomView:overV buttonId:bId];
        }
    }
}

-(void)didInteractWithSubmenu:(NSString *)bId{
    if([bId isEqualToString:[Helper backText]]){
        settings->setApplicationState(GAME_RESULT);
        state = settings->getApplicationState();
        [self animateTopView:header bottomView:footer buttonId:bId];
    } else if ([bId isEqualToString:[Helper retryText]]){
        settings->setApplicationState(GAME_RESULT);
        state = settings->getApplicationState();
        [self animateTopView:header bottomView:footer buttonId:bId];
    }
    
    //BACK BUTTON NEEDS TO STORE CURRENT LEVEL...
}

-(void)showTutorialWithInstructions:(NSArray *)instructions startCount:(int)number{
    
    [Helper releaseViewControllerObject:&tutorialC];
    tutorialC = [[TutorialViewController alloc]initWithStrings:instructions parentRef:self initCounter:number];
    [self addSubview:tutorialC.view];
    [tutorialC show];
}

-(void)animateTopView:(Base *)topV bottomView:(Base *)bottomV buttonId:(NSString *)bId{
    CGRect topFrame;
    CGRect bottomFrame;
    if(settings == NULL){
        return;
    }
    
    if(topV != nil){
        topFrame = topV.frame;
        if(topV.frame.origin.y < 0 ){
            topFrame = topV.initFrame;
        } else {
            topFrame.origin.y = -topFrame.size.height*1.1 - topFrame.origin.y;
        }
    }
    
    if(bottomV != nil){
        bottomFrame = bottomV.frame;
        if(bottomV.frame.origin.y > self.frame.size.height){
            bottomFrame = bottomV.initFrame;
        } else {
            bottomFrame.origin.y = self.frame.size.height - bottomFrame.origin.y - bottomFrame.size.height +  self.frame.size.height;
        }
    }
    [UIView animateWithDuration:[Helper animationTime] animations:^{
        isAnimating = true;
        if(topV != nil){
            topV.frame = topFrame;
        }
        if(bottomV != nil){
            bottomV.frame = bottomFrame;
        }
    } completion:^(BOOL finished) {
        isAnimating = false;
        if(bId == nil){
            return;
        }
        else if(state == MAIN_MENU){
            if([bId isEqualToString:[Helper newGameText]]){
                NSTimeInterval curTime;
                sceneRef->loadNextLevel();
                if(settings->isTutorialActivated()){
                    curTime = 0;
                    [self showTutorialWithInstructions:[Helper memorizeTutorialTips] startCount:0];
                } else {
                    curTime = settings->getInitTime() + settings->getTimeBonus();
                    [self addGameTimer:curTime];
                }
                [header showPrepareMenuWithTime:curTime];
                [footer showPrepareMenuWithTime:curTime];
                [self animateTopView:header bottomView:footer buttonId:nil];
            }
            else if([bId isEqualToString:[Helper settingsText]]){
                settings->setApplicationState(SETTINGS);
                [header loadImageNamed:[Helper settingsImageName]];
                [self animateTopView:header bottomView:settingsV buttonId:nil];
            }
            else if([bId isEqualToString:[Helper rankingText]]){
                settings->setApplicationState(RANKINGS);
                [header loadImageNamed:[Helper rankingImageName]];
                [self animateTopView:header bottomView:rankingV buttonId:nil];
            }
        }
        else if (state == RANKINGS && [bId isEqualToString:[Helper backText]]){
                settings->setApplicationState(MAIN_MENU);
                [header loadImageNamed:[Helper logoImageName]];
                [self animateTopView:header bottomView:footer buttonId:nil];
        }
        else if (state == SETTINGS && [bId isEqualToString:[Helper backText]]){
            settings->setApplicationState(MAIN_MENU);
            [header loadImageNamed:[Helper logoImageName]];
            [self animateTopView:header bottomView:footer buttonId:nil];
        }
        else if (state == GAME_MEMORIZE && [bId isEqualToString:[Helper readyText]]){
            
            NSTimeInterval curTime;
            sceneRef->placeColorPhase();
            if(settings->isTutorialActivated()){
                curTime = 0;
                if(submenuC != nil && submenuC.isSubViewDisplayed){
                    [self interactWithSubmenu];
                }
                [self showTutorialWithInstructions:[Helper placeColorTutorialTips] startCount:5];
                
            } else {
                settings->setTimeBonus(timeLimit);
                curTime = settings->getInitTime() + settings->getTimeBonus();
                [self addGameTimer:curTime];
            }
            [self setCurrentColor];
            [header showPlaceColorMenu:curTime];
            [footer showPlaceColorMenu:curTime];
            [self animateTopView:header bottomView:footer buttonId:nil];
        }
        else if (state == GAME_PLACE_COLORS && [bId isEqualToString:[Helper submitText]]){
            sceneRef->showResultPhaseWithTimeBonus( settings->getTimeBonus() );
            [overV addContentView];
            if(submenuC != nil && submenuC.isSubViewDisplayed){
                [self interactWithSubmenu];
            }
            if(tutorialC != nil){
                [tutorialC hide];
            }
            [self animateTopView:header bottomView:overV buttonId:nil];
            [header showOverviewMenu];
            [footer showOverviewMenu];
        }
        else if (state == GAME_RESULT){
            if([bId isEqualToString:[Helper backText]]){
                [self animateTopView:header bottomView:footer buttonId:nil];
                sceneRef->showMenuMesh();
                [header showMainMenu];
                [footer showMainMenu];
            }
            else if([bId isEqualToString:[Helper retryText]]){
                NSTimeInterval curTime = settings->getInitTime();
                sceneRef->restartGame();
                sceneRef->loadNextLevel();
                if(settings->isTutorialActivated()){
                    curTime = 0;
                    [self showTutorialWithInstructions:[Helper memorizeTutorialTips] startCount:0];
                } else {
                    curTime = settings->getInitTime();
                    [self addGameTimer:curTime];
                }
                [header showPrepareMenuWithTime:curTime];
                [footer showPrepareMenuWithTime:curTime];
                [self animateTopView:header bottomView:footer buttonId:nil];
                
            }
            else if([bId isEqualToString:[Helper nextLevelText]]){
                NSTimeInterval curTime = settings->getInitTime() + settings->getTimeBonus();
                sceneRef->loadNextLevel();
                settings->setTutorialActiveState(false);
                [header showPrepareMenuWithTime:curTime];
                [footer showPrepareMenuWithTime:curTime];
                [self addGameTimer:curTime];
                [self animateTopView:header bottomView:footer buttonId:nil];
            }
        }
        state = settings->getApplicationState();
    }];
}

-(void)addGameTimer:(NSTimeInterval) time{
    timeLimit = time;
    [self clearTimer];
    gametimer = [NSTimer scheduledTimerWithTimeInterval:[Helper timerInterval] target:self selector:@selector(timerCallback:) userInfo:nil repeats:true];
}

-(void)timerCallback:(NSTimer *)timer{
    if(timeLimit == 0){
        if(state == GAME_MEMORIZE){
            [self hideCurrentView:[Helper readyText]];
        } else if (state == GAME_PLACE_COLORS) {
            [self hideCurrentView:[Helper submitText]];
        }
        
        if(gametimer != nil){
            [gametimer invalidate];
            gametimer = nil;
        }
        return;
    }
    
    timeLimit--;
    [self updateLabelsWithValue:timeLimit];
}

-(void)updateLabelsWithValue:(NSTimeInterval)value{
    if(footer == nil || header == nil){
        return;
    }
    if(state == GAME_MEMORIZE){
        [header updatePrepareL:value];
    } else if (state == GAME_PLACE_COLORS){
        [header updateTimeL:value];
    }
}

-(void)clearTimer{
    if(gametimer != nil){
        [gametimer invalidate];
        gametimer = nil;
    }
}

-(UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event{
    UIView *view = [super hitTest:point withEvent:event];
    if( view  == self ){
        return nil;
    }
    return view;
}

-(void)setNextColor{
    if([self isNotNilForSpecificGameState]){
        int color = sceneRef->getCube().getNextColor();
        [header setNextColor:color];
    }
}

-(void)setCurrentColor{
    if([self isNotNilForSpecificGameState]){
        int color = sceneRef->getCube().getCurrentColor();
        [header setNextColor:color];
    }
}

-(UIViewController *)rootViewcontroller{
    return rootControllerRef;
}

-(void)dealloc{
    
    [self clearTimer];
    [Helper releaseViewObject: &header];
    [Helper releaseViewObject: &footer];
    [Helper releaseViewObject:&settingsV];
    [Helper releaseViewObject:&rankingV];
    [Helper releaseViewObject:&overV];
    [Helper releaseViewControllerObject:&submenuC];
    [Helper releaseViewControllerObject:&tutorialC];
    settings = NULL;
    rootControllerRef = nil;
    [super dealloc];
}

@end
