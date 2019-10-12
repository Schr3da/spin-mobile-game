//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>
@class ImageView;

@interface LabelButton : UIButton{
    ImageView *imageV;
    UILabel *titleL;
}

-(instancetype)initWithFrame:(CGRect)frame;
-(void)addLabelWithTitle:(NSString*) title andImage:(UIImage *)image;
-(NSString *)getTitle;
-(void)setNewTitle:(NSString *)title andImageWithName:(NSString *)imageName;

@end
