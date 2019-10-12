//
//  TutorialViewController.h
//  spin
//
//  Created by schr3da on 17/07/15.
//
//


#import <UIKit/UIKit.h>
@class LabelButton;
@class GUI;

@interface TutorialViewController : UIViewController{
    int stepCounter;
    int initCounterNumber;
    UIView *contentView;
    UILabel *headerL;
    UILabel *textL;
    LabelButton *nextB;
    NSArray *strings;
    GUI *guiRef;
}

-(instancetype)initWithStrings:(NSArray *)array parentRef:(GUI *)ref initCounter:(int)number;
-(void)addInstructionWithTitle:(NSString *)title text:(NSString *)text;
-(void)show;
-(void)hide;

@property (readonly) bool isVisible;

@end
