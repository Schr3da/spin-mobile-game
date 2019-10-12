//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#import "Base.h"
@class OverViewController;
@class LabelButton;

@interface Overview : Base <UIAlertViewDelegate> {
    OverViewController *contentController;
    LabelButton *retryB;
    LabelButton *nextB;
    LabelButton *solutionB;
    LabelButton *backB;
    bool isSolutionVisible;
}

-(instancetype)initWithFrame:(CGRect)frame;
-(void)addContentView;

@end
