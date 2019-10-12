//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#import "PositionFactory.h"

@interface RankingViewController : UIViewController <NSURLConnectionDataDelegate, NSURLConnectionDelegate>{
    NSMutableArray *datas;
    Settings *settings;
    CGPoint offset;
    int leadboardPosition;
}

-(instancetype)initWithFrame:(CGRect)frame;

@end
