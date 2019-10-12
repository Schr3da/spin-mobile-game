//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#include "PositionFactory.h"

@interface OverViewController : UIViewController <UIScrollViewDelegate>{
    NSMutableArray *datas;
    CGPoint offset;
    Settings *settings;
}

-(instancetype)initWithFrame:(CGRect)frame;

@end
