//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#import "Base.h"
@class LineLabel;
@class ColorSelector;

@interface HeaderView : Base{
    UIImageView *imageV;
    LineLabel *prepareL;
    LineLabel *stageL;
    LineLabel *timeL;
    ColorSelector *colorL;
}

-(instancetype)initWithFrame:(CGRect)frame;
-(void)loadImageNamed:(NSString *)name;
-(void)showMainMenu;
-(void)showPrepareMenuWithTime:(NSTimeInterval)time;
-(void)showPlaceColorMenu:(NSTimeInterval)time;
-(void)setNextColor:(int)color;
-(void)updatePrepareL:(NSTimeInterval)value;
-(void)updateTimeL:(NSTimeInterval)value;
-(void)showOverviewMenu;
-(int)timeLabelValue;
-(int)prepareLabelValue;

@end
