//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#import "Base.h"
#import "Global.h"
@class LabelButton;

@interface FooterView : Base{
    LabelButton *rankingB;
    LabelButton *newGameB;
    LabelButton *settingsB;
    
    LabelButton *readyB;
    LabelButton *finishB;
}

-(instancetype)initWithFrame:(CGRect)frame;
-(void)showMainMenu;
-(void)showPrepareMenuWithTime:(NSTimeInterval)time;
-(void)showPlaceColorMenu:(NSTimeInterval)time;
-(void)showOverviewMenu;

@end
