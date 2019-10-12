//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>

@interface Base : UIView{
}

-(instancetype)initWithFrame:(CGRect)frame;

@property (readwrite, assign) BOOL curShownOnScreen;
@property (readwrite, assign) CGRect initFrame;

@end
