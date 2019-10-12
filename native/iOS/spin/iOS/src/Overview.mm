//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "Overview.h"
#import "LabelButton.h"
#import "GUI.h"
#import "Helper.h"
#import "OverViewController.h"

@implementation Overview

-(instancetype)initWithFrame:(CGRect)frame{
    
    self = [super initWithFrame:frame];
    if(self != nil){
        contentController = nil;
        backB = nil;
        solutionB = nil;
        nextB = nil;
        retryB = nil;
        isSolutionVisible = false;
        [self addButtons];
    }
    return self;
}

-(void)addButtons{
    int seperator = [Helper seperator];
    CGPoint offset = CGPointMake(0, 0);
    CGSize buttonSize = [Helper buttonSize];
    offset.x += (int) (self.frame.size.width - buttonSize.width * 3 - seperator * 3);
    offset.y = self.frame.size.height- buttonSize.height - [Helper screenBorderOffset];
    
    [Helper releaseViewObject:&backB];
    backB = [[LabelButton alloc]initWithFrame:CGRectMake(   offset.x,
                                                            offset.y,
                                                            buttonSize.width,
                                                            buttonSize.height)];
    
    [backB addLabelWithTitle:[Helper backText] andImage:[UIImage imageNamed:@"backIcon"]];
    [backB addTarget:self action:@selector(dismissView:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:backB];
    offset.x += backB.frame.size.width + seperator;
    
    [Helper releaseViewObject:&solutionB];
    solutionB = [[LabelButton alloc]initWithFrame:CGRectMake(   offset.x,
                                                                offset.y,
                                                                buttonSize.width,
                                                                buttonSize.height)];
    
    [solutionB addLabelWithTitle:[Helper solutionText] andImage:[UIImage imageNamed:@"solutionIcon"]];
    [solutionB addTarget:self action:@selector(solutionView:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:solutionB];
    offset.x += solutionB.frame.size.width + seperator;
    
    [Helper releaseViewObject:&nextB];
    nextB = [[LabelButton alloc]initWithFrame:CGRectMake(   offset.x,
                                                            offset.y,
                                                            buttonSize.width,
                                                            buttonSize.height)];
    
    [nextB addLabelWithTitle:[Helper nextLevelText] andImage:[UIImage imageNamed:@"nextIcon"]];
    [nextB addTarget:self action:@selector(dismissView:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:nextB];
    
    [Helper releaseViewObject:&retryB];
    retryB = [[LabelButton alloc]initWithFrame:CGRectMake(  offset.x,
                                                            offset.y,
                                                            buttonSize.width,
                                                            buttonSize.height)];
    
    [retryB addLabelWithTitle:[Helper retryText] andImage:[UIImage imageNamed:@"retryIcon"]];
    [retryB addTarget:self action:@selector(dismissView:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:retryB];
    offset.x += nextB.frame.size.width + seperator;
}

-(void)dismissView:(id)sender{
    [((GUI *)self.superview) hideCurrentView:[((LabelButton *)sender) getTitle]];
    
}

-(void)solutionView:(id)sender{
    if(contentController == nil){
        return;
    }
    float alpha = (contentController.view.alpha <= 0.0f) ? 0.95f : 0.0f;
    contentController.view.hidden = false;
    [UIView animateWithDuration:[Helper animationTime] animations:^{
        contentController.view.alpha = alpha;
    } completion:^(BOOL finished) {
        contentController.view.hidden = (contentController.view.alpha <= 0.0f) ? true : false;
        isSolutionVisible = contentController.view.hidden;
        ((Scene *)[((GUI *)self.superview) sceneRef])->showSolution();
    }];
}

-(void)updateButtons{
    if(retryB == nil || nextB == nil){
        return;
    }
    Settings &settings = PositionFactory::instance().getSettings();
    if(settings.isLvlPassed()){
        retryB.hidden = true;
        nextB.hidden = !retryB.hidden;
        if(settings.getCurNumberOfRows() == 4 && settings.getCurNumberOfUsedColors() == 4){
            nextB.hidden = true;
            settings.setNewGameDefaultValues();
            UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:[Helper gameCompleteTitle] message:[Helper gameCompleteText] delegate:nil cancelButtonTitle:[Helper dismissText] otherButtonTitles:nil, nil] autorelease];
            [alert show];
        }
    } else {
        retryB.hidden = false;
        nextB.hidden = !retryB.hidden;
        settings.setNewGameDefaultValues();
    }
}

-(void)addContentView{
    CGSize buttonSize = [Helper buttonSize];
    [Helper releaseViewControllerObject:&contentController];
    contentController = [[OverViewController alloc]initWithFrame:CGRectMake(0,
                                                                            0,
                                                                            self.frame.size.width,
                                                                            self.frame.size.height - buttonSize.height - [Helper screenBorderOffset]*2)];
    [self addSubview:contentController.view];
    contentController.view.alpha = 0.95;
    
    [self updateButtons];
}

-(UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event{
    UIView *view = [super hitTest:point withEvent:event];
    if(isSolutionVisible){
        for(UIView *object in view.subviews){
            if(object != nil && object != self && [object pointInside:point withEvent:event]){
                return nil;
            }
        }
    }
    return view;
}

-(void)dealloc{
    [backB removeTarget:self action:@selector(dismissView:) forControlEvents:UIControlEventTouchUpInside];
    [solutionB removeTarget:self action:@selector(solutionView:) forControlEvents:UIControlEventTouchUpInside];
    [nextB removeTarget:self action:@selector(dismissView:) forControlEvents:UIControlEventTouchUpInside];
    [retryB removeTarget:self action:@selector(dismissView:) forControlEvents:UIControlEventTouchUpInside];
    [Helper releaseViewControllerObject:&contentController];
    [Helper releaseViewObject:&backB];
    [Helper releaseViewObject:&solutionB];
    [Helper releaseViewObject:&nextB];
    [Helper releaseViewObject:&retryB];
    [super dealloc];
}

@end
