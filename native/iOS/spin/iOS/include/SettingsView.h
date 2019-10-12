//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#import "Base.h"
@class LabelButton;
@class SettingsViewController;

@interface SettingsView : Base{

    SettingsViewController *contentController;
    LabelButton *backB;
}

-(instancetype)initWithFrame:(CGRect)frame;
-(void)addContentView;

@end
