  //
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "FooterView.h"
#import "LabelButton.h"
#import "Helper.h"
#import "GUI.h"
#import "Settings.h"
#import "PositionFactory.h"
#import "Global.h"

@implementation FooterView

-(instancetype)initWithFrame:(CGRect)frame{
    
    self = [super initWithFrame:frame];
    if(self){
        self.backgroundColor = [UIColor clearColor];
        rankingB = nil;
        newGameB = nil;
        settingsB = nil;
        readyB = nil;
        finishB = nil;
        [self addComponents];
    }
    return self;
}

-(void)addComponents{
    
    CGPoint offset = CGPointMake(0, 0);
    CGSize buttonSize = [Helper buttonSize];
    int seperator = [Helper seperator];
    int buttonWidth = buttonSize.width;
    offset.x += (int) (self.frame.size.width - buttonWidth * 3 - seperator * 3);
    
    [self addNewLabelButton  :&rankingB frame:CGRectMake(offset.x ,0, buttonWidth, self.frame.size.height)
                    imageFile:@"rankingIcon"
                        title:[Helper rankingText]];
    
    offset.x += rankingB.frame.size.width + seperator;
    
    [self addNewLabelButton  :&newGameB frame:CGRectMake(offset.x ,0, buttonWidth, self.frame.size.height)
                    imageFile:@"playIcon"
                        title:[Helper newGameText]];
    
    [self addNewLabelButton  :&readyB frame:CGRectMake(offset.x ,0, buttonWidth, self.frame.size.height)
                    imageFile:@"readyIcon"
                        title:[Helper readyText]];
    
    [self addNewLabelButton  :&finishB frame:CGRectMake(offset.x ,0, buttonWidth, self.frame.size.height)
                    imageFile:@"submitIcon"
                        title:[Helper submitText]];
    
    offset.x += newGameB.frame.size.width + seperator;
    
    [self addNewLabelButton  :&settingsB frame:CGRectMake(offset.x ,0, buttonWidth, self.frame.size.height)
                    imageFile:@"settingsIconw"
                        title:[Helper settingsText]];
    
    [self showMainMenu];
}

-(void)addNewLabelButton:(LabelButton **)button frame:(CGRect)frame imageFile:(NSString *)filename title:(NSString *)title{
    LabelButton *object = *button;
    [Helper releaseViewObject:&object];
    object = [[LabelButton alloc]initWithFrame:frame];
    [object addLabelWithTitle:title andImage:[UIImage imageNamed:filename]];
    [self addSubview:object];
    [object addTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    object.hidden = true;
    *button = object;
}

-(void)showMainMenu{
    rankingB.hidden = false;
    newGameB.hidden = false;
    settingsB.hidden = false;
    readyB.hidden = true;
    finishB.hidden = true;
}

-(void)showPrepareMenuWithTime:(NSTimeInterval)time{
    readyB.hidden = false;
    for (LabelButton *object in self.subviews){
        if(object != readyB){
            object.hidden = true;
        }
    }
}

-(void)showPlaceColorMenu:(NSTimeInterval)time{
    finishB.hidden = false;
    for (LabelButton *object in self.subviews){
        if(object != nil && object != finishB){
            object.hidden = true;
        }
    }
}

-(void)showOverviewMenu{
    for (LabelButton *object in self.subviews){
        if(object != nil){
            object.hidden = true;
        }
    }
}

-(void)action:(id)sender{
    [((GUI*)self.superview) hideCurrentView:((LabelButton *)sender).getTitle];
}

-(void)dealloc{
    
    [rankingB removeTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    [newGameB removeTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    [settingsB removeTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    [readyB removeTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    [finishB removeTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    
    [Helper releaseViewObject:&rankingB];
    [Helper releaseViewObject:&newGameB];
    [Helper releaseViewObject:&settingsB];
    [Helper releaseViewObject:&readyB];
    [Helper releaseViewObject:&finishB];
    [super dealloc];
}

@end
