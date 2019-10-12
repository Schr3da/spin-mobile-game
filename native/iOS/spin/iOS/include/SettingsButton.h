//
//  SettingsButton.h
//  spin
//
//  Created by schr3da on 05/06/15.
//
//

#import <UIKit/UIKit.h>
#include "Settings.h"
@class SettingsContent;

@interface SettingsButton : UIButton{
    SettingsContent *content;
    Settings *settings;
}
-(instancetype)initWithId:(int)bIdRef frame:(CGRect)frame content:(SettingsContent *)contentRef;
@property (readonly, assign, atomic) int bId;

@end


