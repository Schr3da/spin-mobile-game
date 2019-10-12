//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
#import "Base.h"
@class RankingViewController;
@class LabelButton;

@interface RankingView : Base{
    RankingViewController *contentController;
    LabelButton *backB;
}
-(instancetype)initWithFrame:(CGRect)frame;
-(void)addContentView;

@end
