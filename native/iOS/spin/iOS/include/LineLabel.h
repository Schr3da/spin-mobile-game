//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>

@interface LineLabel : UILabel{
    UILabel *_information;
    UILabel *_description;
}

-(instancetype)initWithFrame:(CGRect)frame;
-(void)addLabelWithTitle:(NSString *)information description:(NSString *)description;
-(NSString *)getInformation;
-(void)setInformation:(NSString *)text;
-(NSString *)getDescription;
-(void)setDescription:(NSString *)text;
-(void)setColor:(UIColor *)color;

@end