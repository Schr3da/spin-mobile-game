//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>

@interface ColorSelector : UIButton{
    UIView *colorBox;
    UIView *innerBoxElement;
    UILabel *descriptionL;
}

-(instancetype)initWithFrame:(CGRect)frame;
-(void)setColor:(int)color;

@end
