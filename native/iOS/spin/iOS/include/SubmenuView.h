//
//  SubmenuView.h
//  spin
//
//  Created by schr3da on 10/07/15.
//
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "LabelButton.h"

@interface SubmenuView : UIView{
    
    UILabel *headerL;
    UILabel *textL;
    UIView *backgroundV;
    LabelButton *menuB;
    LabelButton *retryB;
    LabelButton *continueB;

}

-(instancetype)initWithFrame:(CGRect)frame;
-(void)addButtons;

@end

