//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#import "Base.h"
#import "Settings.h"

@interface SettingsViewController : UIViewController{
    NSMutableArray *datas;
    Settings *settings;
    CGPoint offset;
}

-(instancetype)initWithFrame:(CGRect)frame;

@end
